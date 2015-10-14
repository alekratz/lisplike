#ifndef LL_BOOL_EXP
#define LL_BOOL_EXP

#include "ll_tree.hpp"
#include "util.hpp"

class ll_bool_exp
    : public ll_tree
{
public:
    ll_bool_exp(cstref cond_sym, ll_tree_p term1, ll_tree_p term2)
        : cond_sym(cond_sym)
        , term1(term1)
        , term2(term2) { }
    virtual ~ll_bool_exp() = default;

public:
    virtual std::string gencode();

public:
    std::string cond_sym;
    ll_tree_p term1;
    ll_tree_p term2;
};

#endif