#ifndef LL_SET_EXP
#define LL_SET_EXP

#include "ll_tree.hpp"

class ll_set_exp;
typedef std::shared_ptr<ll_set_exp> ll_set_exp_p;

class ll_set_exp
    : public ll_tree, public ll_main
{
public:
    ll_set_exp(cstref identifier, ll_term_p term)
    : identifier(identifier)
    , term(term) { }
    virtual ~ll_set_exp() = default;

public:
    virtual std::string gencode();
    virtual bool main_needs() { return true; }
    virtual std::string genmain() { return gencode(); }    

public:
    std::string identifier;
    ll_term_p term;
};

#endif