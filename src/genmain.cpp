#include "codegen.hpp"
#include "ast.hpp"
#include <string>
#include <sstream>

using namespace std;

std::string genmain(const lisplike_driver& driver)
{
    stringstream result;

    // Append the includes to the top of the main function
    result << driver.includes << endl;
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