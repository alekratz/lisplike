#include "driver.hpp"
#include "scanner.hpp"
#include "parser.hpp"
#include "ast.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <getopt.h>

using namespace std;

lisplike_driver::lisplike_driver()
    : trace_scanning(false)
    , trace_parsing(false)
{

}

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
    // failure
    if(parser.parse() != 0)
        return false;
    // success
    out << ast << endl;
    return true;
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

/*
int lisplike_driver::parse(const string& f)
{
    file = f;
    scan_begin();
    yy::lisplike_parser parser(*this);
    parser.set_debug_level(trace_parsing);
    int res = parser.parse();
    scan_end();
    return res;
}
*/

void lisplike_driver::error (const yy::location& l, const string& m)
{
    cerr << l << ": " << m << endl;
}

void lisplike_driver::error (const string& m)
{
    cerr << m << endl;
}

static vector<string> filenames;
static std::string outdir;
static bool outfile = false;
static bool genheader = false;

static void print_usage(int argc, char **argv)
{
    cout << "usage: " << argv[0] << " [opts] [input1 [input2 input3 ...]]" << endl;
    cout << "opts:" << endl <<
"-p --trace-parsing         traces the Bison parse of the input" << endl <<
"-s --trace-scanning        traces the Lexx scan of the input" << endl <<
"-o --outfile               generate an output file for every output" << endl <<
"-g --gen-header            generate a header file for every output" << endl <<
"-d --dir [outdir]          directory to save output file to" << endl;
}

static void parse_args(int argc, char **argv, lisplike_driver &driver)
{
    while(1)
    {
        int optindex;
        static struct option long_options[] = {
            { "trace-parsing",      no_argument,        0, 'p' },
            { "trace-scanning",     no_argument,        0, 's' },
            { "outfile",            no_argument,        0, 'o' },
            { "gen-header",         no_argument,        0, 'g' },
            { "dir",                required_argument,  0, 'd' },
            { nullptr,              0,                  0,  0  },
        };

        int c = getopt_long(argc, argv, "sph", long_options, &optindex);
        if(c == -1)
            break;
        switch(c)
        {
            case 0:
                cout << long_options[optindex].name << endl;;
                break;
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
            case 'd':
                outdir = argv[optindex];
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

int main(int argc, char **argv)
{
    lisplike_driver driver;
    parse_args(argc, argv, driver);

    if(!filenames.empty())
    {
        for(auto filename : filenames)
        {
        if(!driver.parse_file(filename))
            cerr << "ERROR" << endl;
        else
            cerr << "OK" << endl;
        }
        exit(0);
    }

    string line;
    
    while(getline(cin, line))
    {
        bool result = driver.parse_string(line, "stdin");
        if(result)
            cout << "OK" << endl;
    }
}
