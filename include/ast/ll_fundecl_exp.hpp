#ifndef LL_FUNDECL_EXP
#define LL_FUNDECL_EXP

#include "ll_tree.hpp"
#include "ll_term.hpp"
#include <cassert>

class ll_fundecl_exp;
typedef std::shared_ptr<ll_fundecl_exp> ll_fundecl_exp_p;

class ll_fundecl_exp
    : public ll_tree, public ll_header
{
public:
    ll_fundecl_exp(cstref identifier, ll_children params, ll_children term_list)
    : identifier(identifier)
    , params(params)
    , term_list(term_list) { }
    virtual ~ll_fundecl_exp() = default;

public:
    virtual bool header_needs() { return true; }
    
    virtual std::string gencode();
    virtual std::string genheader();

public:
    std::string identifier;
    ll_children params;
    ll_children term_list;
};

#endif