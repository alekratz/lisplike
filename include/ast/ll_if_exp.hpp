#ifndef LL_IF_EXP_HPP
#define LL_IF_EXP_HPP

#include "ll_tree.hpp"
#include "ll_bool_exp.hpp"
#include "util.hpp"

class ll_if_exp;
typedef std::shared_ptr<ll_if_exp> ll_if_exp_p;

class ll_if_exp
    : public ll_tree
{
public:
    ll_if_exp(ll_bool_exp_p bool_exp, ll_term_p term1, ll_term_p term2)
        : bool_exp(bool_exp)
        , term1(term1)
        , term2(term2) { }
    virtual ~ll_if_exp() = default;

public:
    virtual std::string gencode();

public:
    ll_bool_exp_p bool_exp;
    ll_term_p term1;
    ll_term_p term2;
};

#endif