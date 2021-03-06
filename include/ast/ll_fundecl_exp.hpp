#ifndef LL_FUNDECL_EXP
#define LL_FUNDECL_EXP

#include "ll_tree.hpp"
#include "ll_term.hpp"
#include <cassert>

class ll_fundecl_exp;
typedef std::shared_ptr<ll_fundecl_exp> ll_fundecl_exp_p;

class ll_fundecl_exp
    : public ll_tree, public ll_header, public ll_decl
{
public:

    ll_fundecl_exp(cstref identifier, cstref type, ll_children params, ll_term_p term)
    : identifier(identifier)
    , type(type)
    , params(params)
    , term(term)  { }
    virtual ~ll_fundecl_exp() = default;

public:
    virtual bool header_needs() { return true; }
    
    virtual std::string gencode();
    virtual std::string genheader();
    virtual std::string gendecl() { return ""; }

public:
    std::string identifier;
    std::string type;
    ll_children params;
    ll_term_p term;
};

#endif