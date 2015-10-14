#ifndef LL_BOOL_EXP
#define LL_BOOL_EXP

#include "ll_tree.hpp"
#include "ll_term.hpp"
#include "util.hpp"

class ll_bool_exp;
typedef std::shared_ptr<ll_bool_exp> ll_bool_exp_p;

class ll_bool_exp
    : public ll_tree
{
public:
    ll_bool_exp(cstref cond_sym, ll_term_p term1, ll_term_p term2)
        : cond_sym(cond_sym)
        , term1(term1)
        , term2(term2) { }
    virtual ~ll_bool_exp() = default;

public:
    virtual std::string gencode();

public:
    std::string cond_sym;
    ll_term_p term1;
    ll_term_p term2;
};

#endif