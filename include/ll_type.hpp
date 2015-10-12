#ifndef LL_TYPE_HPP
#define LL_TYPE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cstdint>
#include <cassert>

enum class lisplike_type
{
  str,
//  int64,
  real,
  list,
  dict,
  none,
};

class lisplike_value
{
public:

  lisplike_value()
    : str_value()
    , real_value(0.0)
    , list_value()
    , type(lisplike_type::none)
  {

  }

  lisplike_value(const std::string& val)
    : str_value(val)
    , type(lisplike_type::str)
  { }
  
  lisplike_value(const char *val)
    : str_value(val)
    , type(lisplike_type::str)
  { }

  lisplike_value(const std::vector<lisplike_value>& val)
    : list_value(val)
    , type(lisplike_type::list)
  { }

/*
  lisplike_value(int64_t val)
    : value{ .i = val}
    , type(lisplike_type::int64)
  { }
*/

  lisplike_value(double val)
    : real_value(val)
    , type(lisplike_type::real)
  { }

  /* properties */
public:
  template<typename T>
  T get_value() const;
  template<typename T>
  void set_value(T value);
  template<typename T>
  void operator=(T value) { set_value<T>(value); }

  lisplike_type get_type() const
  {
    return type;
  }

private:
  std::string str_value;
  double real_value;
  std::vector<lisplike_value> list_value;
  lisplike_type type;
};

/* ostream definitions */
std::ostream& operator<<(std::ostream& os, const lisplike_value& ll_val);
std::ostream& operator<<(std::ostream& os, const std::vector<lisplike_value>& ll_vals);

#endif /* LL_TYPE_HPP */
