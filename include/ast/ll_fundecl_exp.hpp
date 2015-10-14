#ifndef LL_FUNDECL_EXP
#define LL_FUNDECL_EXP

#include "ll_tree.hpp"
#include "ll_term.hpp"
#include <cassert>

class ll_fundecl_exp
    : public ll_tree
{
public:
    ll_fundecl_exp(cstref identifier, ll_term_p params, ll_children term_list)
    : identifier(identifier)
    , params(params)
    , term_list(term_list)
    {
        assert(params->type == ll_term_type::list 
            && "Params passed to ll_fundecl_exp AST was a term, but not a list term");
    }
    virtual ~ll_fundecl_exp() = default;

public:
    virtual std::string gencode();

public:
    std::string identifier;
    ll_term_p params;
    ll_children term_list;
};

#endif