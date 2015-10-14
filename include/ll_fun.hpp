#ifndef LL_FUN_HPP
#define LL_FUN_HPP

#include "ll_type.hpp"
#include <vector>
#include <string>

class lisplike_fun
{
public:
  lisplike_fun(const std::vector<lisplike_value>& args, const std::vector<lisplike_value>& lines)
    : args(args)
    , lines(lines)
  { }
  ~lisplike_fun() { }

  /*  */
public:
  std::string gendecl(const std::string& identifier);
  std::string gencall(const std::string& identifier, const std::vector<lisplike_value>& params);

private:
  std::vector<lisplike_value> args;
  std::vector<lisplike_value> lines;
  
};

#endif
