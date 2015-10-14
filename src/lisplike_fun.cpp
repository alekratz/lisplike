#include "ll_fun.hpp"
#include "format.hpp"

using namespace std;

string lisplike_fun::gendecl(const string& identifier)
{
  return "";
  //return format("auto % = [&] {\n%\n};", identifier, linestr;
}

std::string lisplike_fun::gencall(const string& identifier, const vector<lisplike_value>& params)
{
  return format("%(%);", identifier, params);
}

