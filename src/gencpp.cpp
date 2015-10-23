#include "codegen.hpp"
#include "ast.hpp"
#include <sstream>

using namespace std;

string gencpp(const lisplike_driver& driver)
{
    stringstream result;

    result << driver.includes << endl;

    for(auto ll_child : driver.ast)
    {
        if(!ll_child->main_needs())
            result << ll_child->gencode() << endl;
    }
    return result.str();
}
