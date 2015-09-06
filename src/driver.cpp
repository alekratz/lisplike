#include "driver.hpp"
#include "scanner.hpp"
#include "parser.hpp"

#include <fstream>
#include <sstream>

lisplike_driver::lisplike_driver()
  : trace_scanning(false)
  , trace_parsing(false)
{

}

lisplike_driver::~lisplike_driver()
  { }

bool lisplike_driver::parse_stream(std::istream& in, const std::string& sname)
{
  streamname = sname;
  lisplike_scanner scanner(&in);
  scanner.set_debug(trace_scanning);
  lexer = &scanner;
  yy::lisplike_parser parser(*this);
  parser.set_debug_level(trace_parsing);
  return parser.parse() == 0;
}

bool lisplike_driver::parse_string(const std::string& line, const std::string& sname)
{
  std::istringstream iss(line);
  return parse_stream(iss, sname);
}

bool lisplike_driver::parse_file(const std::string& filename)
{
  std::ifstream in(filename);
  if(!in.good()) return false;
  return parse_stream(in, filename);
}

/*
int lisplike_driver::parse(const std::string& f)
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

void lisplike_driver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void lisplike_driver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}

int main()
{
  using namespace std;

  string line;
  lisplike_driver driver;
  //driver.trace_scanning = true;
  //driver.trace_parsing = true;
  while(getline(cin, line))
  {
    bool result = driver.parse_string(line, "stdin");
  }
}