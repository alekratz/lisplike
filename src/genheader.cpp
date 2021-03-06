#include "codegen.hpp"
#include "format.hpp"
#include "ast.hpp"
#include <uuid.h>

#define UUID_LEN 36

using namespace std;

string ll_let_exp::genheader()
{
    if(is_mutable)
        return format("extern ll_value %;", identifier);
    else
        return format("extern const ll_value %;", identifier);
}

string ll_fundecl_exp::genheader()
{
    return format("extern % %(ll_value %);", type, identifier, pad_internal(params, ", ll_value "));
}

string genheader(const lisplike_driver& driver)
{
    stringstream result;

    // UUID for the header include guard
    char uuid_buf[UUID_LEN];
    uuid_t uuid_gen;
    uuid_generate_random(uuid_gen);
    uuid_unparse(uuid_gen, uuid_buf);
    for(int i = 0; i < UUID_LEN; i++)
    {
        if(uuid_buf[i] == '-')
            uuid_buf[i] = '_';
    }

    result << "#ifndef " << "_" << uuid_buf << endl;
    result << "#define " << "_" << uuid_buf << endl;
    result << driver.includes << endl;
    // Declare header decls
    for(auto ll_child : driver.ast)
    {
        // does our header need this child in the AST?
        if(ll_child->header_needs())
            result << dynamic_pointer_cast<ll_header>(ll_child)->genheader() << endl;
        // otherwise... ignore
    }
    result << "#endif" << endl;
    return result.str();
}