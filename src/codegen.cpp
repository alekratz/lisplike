#include "codegen.hpp"
#include "ast.hpp"
#include "format.hpp"
#include <string>
#include <sstream>

using namespace std;

string ll_let_exp::genheader()
{
    return format("extern ll_type %;", identifier);
}

string ll_fundecl_exp::genheader()
{
    return format("extern ll_type %(%);", identifier, params);
}

string gen_header(const ll_children& tree)
{
    stringstream result;
    // Declare header decls
    for(auto ll_child : tree)
    {
        // does our header need this child in the AST?
        if(ll_child->header_needs())
            result << dynamic_pointer_cast<ll_header>(ll_child)->genheader() << endl;
        // otherwise... ignore
    }
    return result.str();
}

string gen_cpp(const ll_children& tree)
{
    stringstream result;
    for(auto ll_child : tree)
    {
        if(!ll_child->main_needs())
            result << ll_child->gencode() << endl;
    }
    return result.str();
}

string gen_main(const ll_children& tree)
{
    stringstream result;
    result << "int main(int argc, char **argv) {" << endl;
    for(auto ll_child : tree)
    {
        if(ll_child->main_needs())
            result << dynamic_pointer_cast<ll_main>(ll_child)->genmain() << endl;
    }
    result << "}";
    return result.str();
}
