#ifndef LL_TREE_HPP
#define LL_TREE_HPP

#include <memory>
#include <string>
#include <vector>

class ll_tree;

typedef std::shared_ptr<ll_tree> ll_tree_p;
typedef std::vector<ll_tree_p> ll_children;

class ll_tree
{
public:
    ll_tree() = default;
    virtual ~ll_tree() = default;

public:
    virtual std::string gencode() = 0;
};

std::ostream& operator<<(std::ostream& os, const ll_tree_p& tree);
std::ostream& operator<<(std::ostream& os, const ll_children& children);

#endif