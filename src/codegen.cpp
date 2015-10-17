#include "codegen.hpp"
#include "ast.hpp"
#include "format.hpp"
#include <string>
#include <sstream>
#include <set>

using namespace std;

string ll_let_exp::genheader()
{
    return format("extern ll_value %;", identifier);
}

string ll_fundecl_exp::genheader()
{
    return format("extern ll_value %(ll_value %);", identifier, params);
}

string gen_header(const lisplike_driver& driver)
{
    stringstream result;
    // TODO: include guard
    for(auto inc : driver.includes)
        result << inc->gencode() << endl;
    // Declare header decls
    for(auto ll_child : driver.ast)
    {
        // does our header need this child in the AST?
        if(ll_child->header_needs())
            result << dynamic_pointer_cast<ll_header>(ll_child)->genheader() << endl;
        // otherwise... ignore
    }
    return result.str();
}

string gen_cpp(const lisplike_driver& driver)
{
    stringstream result;

    for(auto inc : driver.includes)
        result << inc->gencode() << endl;

    for(auto ll_child : driver.ast)
    {
        if(!ll_child->main_needs())
            result << ll_child->gencode() << endl;
    }
    return result.str();
}

string gen_main(const lisplike_driver& driver)
{
    stringstream result;

    // Append the includes to the top of the main function
    for(auto inc : driver.includes)
        result << inc->gencode() << endl;

    // Create the main function
    result << "int main(int argc, char **argv) {" << endl;
    for(auto ll_child : driver.ast)
    {
        if(ll_child->main_needs())
            result << dynamic_pointer_cast<ll_main>(ll_child)->genmain() << ';' << endl;
    }
    result << "}";
    return result.str();
}
