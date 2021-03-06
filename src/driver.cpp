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
    reset();
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
bool verbose = false;
static bool outfile = true;
static bool should_genheader = true;
static bool should_genmain = true;

static void print_usage(int argc, char **argv)
{
    cout << "usage: " << argv[0] << " [opts] [input1 [input2 input3 ...]]" << endl;
    cout << "opts:" << endl <<
    "-p --trace-parsing         traces the Bison parse of the input" << endl <<
    "-s --trace-scanning        traces the Lexx scan of the input" << endl <<
    "-o --no-outfile            don't generate an output file" << endl <<
    "-h --no-header             don't generate a header file" << endl <<
    "-m --no-main               don't generate a main file" << endl <<
    "-d --dir [outdir]          directory to save output file to" << endl <<
    "-v --verbose               verbose output" << endl <<
    "-? --help                  shows this help message" << endl;
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
            { "gen-header",         no_argument,        0,  'h' },
            { "gen-main",           no_argument,        0,  'm' },
            { "dir",                required_argument,  0,  'd' },
            { "verbose",            no_argument,        0,  'v' },
            { "help",               required_argument,  0,  '?' },
            { nullptr,              0,                  0,   0  },
        };

        int c = getopt_long(argc, argv, "sphogmd:v", long_options, &optindex);
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
                outfile = false;
                break;
            case 'h':
                should_genheader = false;
                break;
            case 'm':
                should_genmain = false;
                break;
            case 'd':
                outdir = path(optarg);
                break;
            case 'v':
                verbose = true;
                break;
            case '?':
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

static int do_codegen(function<string(const lisplike_driver&)> codegen_fn, 
    const lisplike_driver& driver, const path& filename)
{
    path outpath = outdir / (path(filename).filename());
    ofstream out_stream(outpath.string());
    if(!out_stream.good())
    {
        cerr << "could not open " << outpath << endl;
        return 1;
    }
    VCERR << "generating " << outpath.string() << endl;
    out_stream << codegen_fn(driver);
    return 0;
}

int main(int argc, char **argv)
{
    int mainresult = 0;
    lisplike_driver driver;
    parse_args(argc, argv, driver);

    if(!filenames.empty())
    {
        ll_children ast;
        ll_inc_list includes;
        if(!create_directory_tree(outdir))
        {
            cerr << "could not create directory tree " << outdir << endl;
            return 1;
        }

        for(path filename : filenames)
        {
            cerr << filename.string() << endl;
            if(!driver.parse_file(filename.string()))
            {
                cerr << "error in " << filename << endl;
                return 1;
            }
            else
            {
                ast.insert(ast.end(), driver.ast.begin(), driver.ast.end());
                includes.insert(driver.includes.begin(), driver.includes.end());
                if(should_genheader)
                {
                    // add this path to the master list of includes for main.cpp
                    mainresult |= do_codegen(genheader, driver, filename.replace_extension(".hpp"));
                    // also add this generated header to driver itself so that it gets included in the cpp file
                    auto include = make_shared<ll_inc>(false,
                        (outdir / filename.filename()).replace_extension("").string());
                    includes.insert(include);
                    driver.includes.insert(include);
                }

                if(outfile)
                    mainresult |= do_codegen(gencpp, driver, filename.replace_extension(".cpp"));
            }
        }

        if(should_genmain)
        {
            // HACK : come up with something better than this...
            lisplike_driver carrier;
            carrier.ast = ast;
            carrier.includes = includes;
            mainresult |= do_codegen(genmain, carrier, path("main.cpp"));
        }

        if(mainresult == 0)
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
    return mainresult;
}
