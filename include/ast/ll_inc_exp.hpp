#ifndef LL_INC_EXP_HPP
#define LL_INC_EXP_HPP

#include "ll_tree.hpp"

class ll_inc_exp;
typedef std::shared_ptr<ll_inc_exp> ll_inc_exp_p;

class ll_inc_exp
    : public ll_tree, public ll_header
{
public:
    ll_inc_exp(bool is_native, cstref path)
    : is_native(is_native)
    , path(path) { }
    virtual ~ll_inc_exp() = default;

public:
    virtual std::string gencode();
    virtual bool header_needs() { return true; }

public:
    bool is_native;
    std::string path;

public:
    virtual std::string genheader() { return gencode(); }
};

#endif