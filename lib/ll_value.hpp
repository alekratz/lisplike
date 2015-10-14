#ifndef LL_VALUE_HPP
#define LL_VALUE_HPP

#include <string>
#include <vector>

/*
 * This file is a representation of a Lisp-Like value. It's designed to be
 * dynamically assigned, so while it may hold many values at once, it only has
 * one interpreted value that can be used.
 *
 * Mixing and matching will come later.
 */

enum class ll_value_type
{
    str,
    real,
    fun,
    list,
};

typedef const std::string& cstref;
typedef std::vector<ll_value_p> ll_value_list;

class ll_value
{
public:
    ll_value(cstref val)
        : str_val(val)
        , type(ll_value_type::str) { }
    ll_value(const char *val)
        : str_val(val)
        , type(ll_value_type::str) { }
    ll_value(long double val)
        : real_val(val)
        , type(ll_value_type::real) { }
    ll_value(ll_value_list val)
        : list_val(val)
        , type(ll_value_type::list) { }

private:
    std::string str_val;
    long double real_val;
    ll_value_list list_val;
};

#endif
