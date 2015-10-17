#ifndef LL_BLOCk_EXP_HPP
#define LL_BLOCk_EXP_HPP

#include "ll_tree.hpp"

class ll_block_exp;
typedef std::shared_ptr<ll_block_exp> ll_block_exp_p;

class ll_block_exp
    : public ll_tree, public ll_main
{
public:
    ll_block_exp(const ll_children& children)
        : children(children) { }
    virtual ~ll_block_exp() = default;

    virtual bool main_needs() { return true; }

    virtual std::string gencode();
    virtual std::string genmain() { return gencode(); }

public:
    ll_children children;
};

#endif