#ifndef LL_IF_EXP_HPP
#define LL_IF_EXP_HPP

#include "ll_tree.hpp"
#include "util.hpp"

class ll_if_exp
    : public ll_tree
{
public:
    ll_if_exp(ll_tree_p cond_exp, ll_tree_p term1, ll_tree_p term2)
        : cond_exp(cond_exp)
        , term1(term1)
        , term2(term2) { }
    virtual ~ll_if_exp() = default;

public:
    virtual std::string gencode();

public:
    ll_tree_p cond_exp;
    ll_tree_p term1;
    ll_tree_p term2;
};

#endif