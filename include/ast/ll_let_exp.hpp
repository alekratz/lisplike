#ifndef LL_LET_EXP
#define LL_LET_EXP

#include "ll_tree.hpp"

class ll_let_exp;
typedef std::shared_ptr<ll_let_exp> ll_let_exp_p;

class ll_let_exp
    : public ll_tree
{
public:
    ll_let_exp(cstref identifier, ll_term_p term)
    : identifier(identifier)
    , term(term) { }
    virtual ~ll_let_exp() = default;

public:
    virtual std::string gencode();

public:
    std::string identifier;
    ll_term_p term;
};

#endif