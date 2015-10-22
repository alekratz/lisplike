#ifndef LL_INC_EXP_HPP
#define LL_INC_EXP_HPP

#include "ll_tree.hpp"
#include <unordered_set>
#include <iostream>

class ll_inc;
typedef std::shared_ptr<ll_inc> ll_inc_p;
typedef std::unordered_set<ll_inc_p> ll_inc_list;

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

namespace std
{
template<>
struct hash<ll_inc_p>
{
    size_t operator()(const ll_inc_p& ptr) const
        { return hash<string>()(ptr->path.c_str()) + ptr->is_native; }
};

template<>
struct equal_to<ll_inc_p>
{
    bool operator()(const ll_inc_p& p1, const ll_inc_p& p2) const
    {
        return hash<ll_inc_p>()(p1) == hash<ll_inc_p>()(p2);
    }
};
}

inline std::ostream& operator<<(std::ostream& os, const ll_inc_list& includes)
{
    for(auto inc : includes)
        os << inc->gencode() << "\n";
    return os;
}

#endif
