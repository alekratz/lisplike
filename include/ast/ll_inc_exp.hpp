#ifndef LL_INC_EXP_HPP
#define LL_INC_EXP_HPP

#include "ll_tree.hpp"

class ll_inc_exp;
typedef std::shared_ptr<ll_inc_exp> ll_inc_exp_p;

class ll_inc_exp
    : public ll_tree
{
public:
    ll_inc_exp(cstref path)
    : path(path) { }
    virtual ~ll_inc_exp() = default;

public:
    virtual std::string gencode();

public:
    std::string path;
};

#endif