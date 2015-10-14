#include "ll_type.hpp"
#include "format.hpp"
#include <string>

using namespace std;

string ll_fundecl::gencode()
{
  string linestr = "";
  for(auto line : lines)
  {
    if(line != nullptr)
      linestr += line->gencode() + "\n";
  }
  return linestr;
}

string ll_funcall::gencode()
{
  return "";
}

string ll_value::gencode()
{
  switch(type)
  {
    case ll_type::str:
      return str_val;
    case ll_type::real:
      return format("%", real_val);
    case ll_type::dict:
      assert(false && "unreachable");
      break;
    case ll_type::list:
      return format("%", list_val);
    case ll_type::none:
      return "None";
  }
  return "";
}

string ll_let::gencode()
{
  return format("ll_value % = %;", identifier, value->gencode());
}

ostream& operator<<(ostream& os, const ll_line_p& ll_line)
{
  os << ll_line->gencode();
  return os;
}

ostream& operator<<(ostream& os, const ll_line_vec& ll_vals)
{
  for(auto ll : ll_vals)
    os << ll->gencode() << " ";
  return os;
}
