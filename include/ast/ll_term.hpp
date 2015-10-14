#ifndef LL_TERM_EXP
#define LL_TERM_EXP

#include "ll_tree.hpp"

enum class ll_term_type
{
    str,
    real,
    list,
//    dict,
};

class ll_term;
typedef std::shared_ptr<ll_term> ll_term_p;

class ll_term
    : public ll_tree
{
public:
    ll_term(long double val) 
        : real_val(val)
        , type(ll_term_type::real) { }
    ll_term(cstref val)
        : str_val(val)
        , type(ll_term_type::str) { }
    ll_term(const char *val)
        : str_val(val)
        , type(ll_term_type::str) { }
    ll_term(const ll_children& val)
        : list_val(val)
        , type(ll_term_type::list) { }
    virtual ~ll_term() = default;

public:
    virtual std::string gencode();

public:
    std::string str_val;
    long double real_val;
    ll_children list_val;
    // TODO : dict_value
    ll_term_type type;

};

#endif