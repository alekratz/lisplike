#include "ll_type.hpp"

using namespace std;

/* getters */
template<>
double lisplike_value::get_value() const { return real_value; }
template<>
const string& lisplike_value::get_value() const { return str_value; }
template<>
const vector<lisplike_value> lisplike_value::get_value() const { return list_value; }

template<>
void lisplike_value::set_value(const string& value)
{
  type = lisplike_type::str;
  str_value = value;
}

/*
 * Warning: don't use this when you're doing regular coding - attempt to use
 * the const string& instead - this prevents unnecessary copying.
 */
template<>
void lisplike_value::set_value(string value)
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

template<>
void lisplike_value::set_value(const vector<lisplike_value>& list)
{
  type = lisplike_type::list;
  list_value = list;
}

template<>
void lisplike_value::set_value(vector<lisplike_value> list)
{
  type = lisplike_type::list;
  list_value = list;
}

ostream& operator<<(ostream& os, const lisplike_value& ll_val)
{
  switch(ll_val.get_type())
  {
    case lisplike_type::str:
      os << ll_val.get_value<const string&>();
      break;
    case lisplike_type::real:
      os << ll_val.get_value<double>();
      break;
    case lisplike_type::list:
      os << ll_val;
      break;
    case lisplike_type::dict:
      assert(false && "Unreachable code reached");
      break;
    case lisplike_type::none:
      os << "None";
      break;
  }
  return os;
}

ostream& operator<<(ostream& os, const vector<lisplike_value>& ll_vals)
{
  for(auto ll : ll_vals)
    os << ll << " ";
  return os;
}
