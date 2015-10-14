#ifndef LL_FUNCALL_EXP
#define LL_FUNCALL_EXP

#include "ll_tree.hpp"
#include "util.hpp"

class ll_funcall_exp
    : public ll_tree
{
public:
    ll_funcall_exp(cstref identifier, ll_children term_list)
        : identifier(identifier)
        , term_list(term_list) { }
    virtual ~ll_funcall_exp() = default;

public:
    virtual std::string gencode();

public:
    std::string identifier;
    ll_children term_list;
};

#endif