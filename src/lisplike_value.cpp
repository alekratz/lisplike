#include "ll_type.hpp"

/* getters */
template<>
double lisplike_value::get_value() const { return real_value; }
template<>
const std::string& lisplike_value::get_value() const { return str_value; }

template<>
void lisplike_value::set_value(const std::string& value)
{
  type = lisplike_type::str;
  str_value = value;
}

template<>
void lisplike_value::set_value(double value)
{
  type = lisplike_type::real;
  real_value = value;
}

std::ostream& operator<<(std::ostream& os, const lisplike_value& ll_val)
{
  switch(ll_val.get_type())
  {
    case lisplike_type::str:
      os << ll_val.get_value<const std::string&>();
      break;
    case lisplike_type::real:
      os << ll_val.get_value<double>();
      break;
    case lisplike_type::dict:
      assert(false && "Unreachable code reached");
      break;
    case lisplike_type::none:
      os << "None";
  }
  return os;
}
