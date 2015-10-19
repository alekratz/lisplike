#include "ast.hpp"
#include "format.hpp"
#include "util.hpp"
#include <string>
#include <sstream>

using namespace std;

string ll_fundecl_exp::gencode()
{
    stringstream builder;
    builder << "ll_value " << identifier;
    builder << "(ll_value " << pad_internal(params, ", ll_value ") << ")";
    builder << " {" << endl;
    builder << format("return %;", term->gencode()) << endl;
    builder << "}" << endl;
    return builder.str();
}

string ll_funcall_exp::gencode()
{
    string termstr = pad_internal(term_list, ", ");
    return format("%(%)", identifier, termstr);
}

string ll_let_exp::gencode()
{
    if(is_mutable)
        return format("ll_value % = %;", identifier, term->gencode());
    else
        return format("const ll_value % = %;", identifier, term->gencode());
}

string ll_set_exp::gencode()
{
    return format("% = %;", identifier, term->gencode());
}

string ll_if_exp::gencode()
{
    return format("((%) ? (%) : (%))", cond_exp->gencode(), term1->gencode(), term2->gencode());
//    return format("[&](){if(%) { return %; } else { return %; }}()", bool_exp->gencode(), term1->gencode(), term2->gencode());
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

string ll_block_exp::gencode()
{
    stringstream builder;
    builder << "[&]() -> ll_value {" << endl;
    for(auto it = children.begin(); it != children.end(); it++)
    {
        if(it + 1 == children.end())
            builder << "return " << (*it)->gencode() << ";" << endl;
        else
            builder << (*it)->gencode() << ";" << endl;
    }
    builder << "}()" << endl;
    return builder.str();
}

string ll_inc::gencode()
{
    /* 
    in clang 3.7, this segfaults the compiler. It just has the removed "int" declaration. Not sure why.
    return format("#include \"%.hpp\"", trim(path, [](i){ return i == '"'; }));
    */
    if(is_native)
        return format("#include <%>", path);
    else
        return format("#include \"%.hpp\"", path);
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
            return format("{ % }", pad_internal(list_val, ", "));
            /*
        case ll_term_type::dict:
            */
        case ll_term_type::exp:
            return exp_val->gencode();
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

ostream& operator<<(ostream& os, const ll_inc_list& includes)
{
    for(auto inc : includes)
        os << inc->gencode() << "\n";
    return os;
}