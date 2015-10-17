#ifndef LL_INC_EXP_HPP
#define LL_INC_EXP_HPP

#include "ll_tree.hpp"

class ll_inc;
typedef std::shared_ptr<ll_inc> ll_inc_p;
typedef std::vector<ll_inc_p> ll_inc_list;

class ll_inc
    : public ll_tree
{
public:
    ll_inc(bool is_native, cstref path)
    : is_native(is_native)
    , path(path) { }
    virtual ~ll_inc() = default;

public:
    virtual std::string gencode();
    virtual bool header_needs() { return true; }

public:
    bool is_native;
    std::string path;
};

std::ostream& operator<<(std::ostream& os, const ll_inc_list& includes);

#endif