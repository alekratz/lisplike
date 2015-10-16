#include "driver.hpp"
#include "scanner.hpp"
#include "parser.hpp"
#include "ast.hpp"
#include "codegen.hpp"

#include <sstream>
#include <vector>
#include <cstdlib>
#include <getopt.h>
#include <fstream>
#include <functional>
#include <boost/filesystem.hpp>

using namespace std;
using boost::filesystem::path;

lisplike_driver::lisplike_driver()
    : trace_scanning(false)
    , trace_parsing(false) { }

lisplike_driver::~lisplike_driver()
    { }

bool lisplike_driver::parse_stream(istream& in, const string& sname, std::ostream& out)
{
    streamname = sname;
    lisplike_scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    lexer = &scanner;
    yy::lisplike_parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return parser.parse() == 0;
}

bool lisplike_driver::parse_string(const string& line, const string& sname, std::ostream& out)
{
    istringstream iss(line);
    return parse_stream(iss, sname);
}

bool lisplike_driver::parse_file(const string& filename, std::ostream& out)
{
    ifstream in(filename);
    if(!in.good()) return false;
    return parse_stream(in, filename);
}

void lisplike_driver::error (const yy::location& l, const string& m)
{
    cerr << l << ": " << m << endl;
}

void lisplike_driver::error (const string& m)
{
    cerr << m << endl;
}

static vector<string> filenames;
static path outdir = ".";
static bool outfile = false;
static bool genheader = false;
static bool genmain = false;

static void print_usage(int argc, char **argv)
{
    cout << "usage: " << argv[0] << " [opts] [input1 [input2 input3 ...]]" << endl;
    cout << "opts:" << endl <<
"-p --trace-parsing         traces the Bison parse of the input" << endl <<
"-s --trace-scanning        traces the Lexx scan of the input" << endl <<
"-o --outfile               generate an output file for every output" << endl <<
"-g --gen-header            generate a header file for every output" << endl <<
"-m --gen-main              generate a main file, containing every top level " << endl <<
"                               function call, in order of the files passed to " << endl <<
"                               the command line." << endl <<
"-d --dir [outdir]          directory to save output file to" << endl;
}

static void parse_args(int argc, char **argv, lisplike_driver &driver)
{
    while(1)
    {
        int optindex;
        static struct option long_options[] = {
            { "trace-parsing",      no_argument,        0,  'p' },
            { "trace-scanning",     no_argument,        0,  's' },
            { "outfile",            no_argument,        0,  'o' },
            { "gen-header",         no_argument,        0,  'g' },
            { "gen-main",           no_argument,        0,  'm' },
            { "dir",                required_argument,  0,  'd' },
            { nullptr,              0,                  0,   0  },
        };

        int c = getopt_long(argc, argv, "sphogmd:", long_options, &optindex);
        if(c == -1)
            break;
        switch(c)
        {
            case 's':
                driver.trace_scanning = true;
                break;
            case 'p':
                driver.trace_parsing = true;
                break;
            case 'o':
                outfile = true;
                break;
            case 'g':
                genheader = true;
                break;
            case 'm':
                genmain = true;
                break;
            case 'd':
                outdir = path(optarg);
                break;
            case '?':
            case 'h':
                print_usage(argc, argv);
                exit(0);
                break;
            default:
                break;
        }
    }
    
    while(optind < argc)
        filenames.push_back(argv[optind++]);
    for(; optind < argc; optind++)
        cerr << "ignoring input file: " << argv[optind] << endl;
}

static void do_codegen(function<string(const ll_children&)> codegen_fn, 
    const ll_children& ast, cstref filename)
{
    path outpath = outdir / (path(filename).filename());
    ofstream out_stream(outpath.string());
    if(!out_stream.good())
    {
        cerr << "could not open " << outpath << endl;
        exit(1);
    }
    out_stream << codegen_fn(ast);
}

int main(int argc, char **argv)
{
    lisplike_driver driver;
    parse_args(argc, argv, driver);

    if(!filenames.empty())
    {
        ll_children ast;
        for(auto filename : filenames)
        {
            if(!driver.parse_file(filename))
            {
                cerr << "ERROR" << endl;
                exit(1);
            }
            else
            {
                ast.insert(ast.end(), driver.ast.begin(), driver.ast.end());
                if(outfile)
                    do_codegen(gen_cpp, driver.ast, filename + ".cpp");
                if(genheader)
                    do_codegen(gen_header, driver.ast, filename + ".hpp");
            }
        }
        if(genmain)
            do_codegen(gen_main, ast, "main.cpp");
        cerr << "OK" << endl;
    }
    else
    {
        string line;
        while(getline(cin, line))
        {
            bool result = driver.parse_string(line, "stdin");
            if(result)
                cout << "OK" << endl;
        }
    }
    return 0;
}
