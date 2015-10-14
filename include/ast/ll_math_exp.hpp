#ifndef LL_MATH_EXP_HPP
#define LL_MATH_EXP_HPP

#include "ll_tree.hpp"
#include "util.hpp"

class ll_math_exp
    : public ll_tree
{
public:
    ll_math_exp(cstref math_op, ll_children term_list) 
        : math_op(math_op)
        , term_list(term_list) { }
    virtual ~ll_math_exp() = default;

public:
    virtual std::string gencode();

public:
    std::string math_op;
    ll_children term_list;
};

#endif