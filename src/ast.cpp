#include "ast.hpp"
#include "format.hpp"
#include "util.hpp"
#include <string>

using namespace std;

string ll_fundecl_exp::gencode()
{
    string linestr = "ll_value " + identifier;
    linestr += "(";
    linestr += pad_internal(params->list_val, ", ");
    linestr += ") {\n";
    for(auto line : term_list)
        linestr += "\t" + line->gencode() + "\n";
    linestr += "}\n";
    return linestr;
}

string ll_funcall_exp::gencode()
{
    string termstr = pad_internal(term_list, ", ");
    return format("%(%)", identifier, termstr);
}

string ll_let_exp::gencode()
{
    return format("ll_value % = %;", identifier, term->gencode());
}

string ll_if_exp::gencode()
{
    return format("if(%) { \nreturn %;\n} else {\n %;\n}", cond_exp->gencode(), term1->gencode(), term2->gencode());
}

string ll_bool_exp::gencode()
{
    // maybe surround this with parens later
    return format("% % %", term1->gencode(), cond_sym, term2->gencode());
}

string ll_math_exp::gencode()
{
    string math_exp = "(";
    math_exp += pad_internal(term_list, math_op);
    math_exp += ")";
    return math_exp;
}

string ll_term::gencode()
{
    switch(type)
    {
        case ll_term_type::str:
            return str_val;
        case ll_term_type::real:
            return format("%", real_val);
        case ll_term_type::list:
            return format("%", list_val);
            /*
        case ll_term_type::dict:
            */
        default:
            assert(false && "unreachable");
            break;
    }
    return "";
}

ostream& operator<<(ostream& os, const ll_tree_p& ll_tree)
{
    os << ll_tree->gencode();
    return os;
}

ostream& operator<<(ostream& os, const ll_children& children)
{
    for(auto ll : children)
        os << ll->gencode() << "\n";
    return os;
}
