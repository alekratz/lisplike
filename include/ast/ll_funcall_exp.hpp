#ifndef LL_FUNCALL_EXP
#define LL_FUNCALL_EXP

#include "ll_tree.hpp"
#include "util.hpp"

class ll_funcall_exp;
typedef std::shared_ptr<ll_funcall_exp> ll_funcall_exp_p;

class ll_funcall_exp
    : public ll_tree, public ll_main
{
public:
    ll_funcall_exp(cstref identifier, ll_children term_list)
        : identifier(identifier)
        , term_list(term_list) { }
    virtual ~ll_funcall_exp() = default;

public:
    virtual std::string gencode();
    virtual bool main_needs() { return true; }
    virtual std::string genmain() { return gencode(); }

public:
    std::string identifier;
    ll_children term_list;
};

#endif