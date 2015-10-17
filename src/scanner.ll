%option c++ noyywrap nounput batch debug noinput

%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cstdint>
#include <string>
#include "driver.hpp"
#include "scanner.hpp"
#include "parser.hpp"

#define YY_USER_ACTION loc.columns(yyleng);

# undef yywrap
# define yywrap() 1

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-register"
%}

/* keywords */
fun_keyw    fun
let_keyw    let
if_keyw     if
inc_keyw    inc
native_keyw native
none_keyw   none

/* symbols */
lparen        \(
rparen        \)
squot         \'
dquot         \"
/* ignore the weird comment/double quote - syntax highlighting isn't smart enough to pick up the escaped quote "*/

/* literals */
string      {dquot}[^\n]*{dquot}
ws          [\t ]
newline     \n
alpha       [a-zA-Z]
dig         [0-9]

/* delimiters */
equals      =

/* function names */
math_op     \+|-|\*|\/
bool_op     =|<|>
ident       ({alpha}|_)({alpha}|_|{dig})*
num         {dig}+
cond_sym    {bool_op}{bool_op}?
comment     ;[^\n]*{newline}

%%

%{
// call this every time yylex is called
loc.step();
%}

{newline}       { loc.lines(yyleng); loc.step(); }
{ws}            loc.step();
{comment}       { loc.lines(1); }
{equals}        return yy::lisplike_parser::make_EQUALS(loc);
{fun_keyw}      return yy::lisplike_parser::make_FUN_KEYW(loc);
{let_keyw}      return yy::lisplike_parser::make_LET_KEYW(loc);
{if_keyw}       return yy::lisplike_parser::make_IF_KEYW(loc);
{inc_keyw}      return yy::lisplike_parser::make_INC_KEYW(loc);
{native_keyw}   return yy::lisplike_parser::make_NATIVE_KEYW(loc);
{none_keyw}     return yy::lisplike_parser::make_NONE_KEYW(loc);
{string}        return yy::lisplike_parser::make_STRING(yytext, loc);
{ident}         return yy::lisplike_parser::make_IDENTIFIER(yytext, loc);
{cond_sym}      return yy::lisplike_parser::make_COND_SYM(yytext, loc);
{math_op}       return yy::lisplike_parser::make_MATH_OP(yytext, loc);
{num}           {
    errno = 0;
    int64_t val = strtol(yytext, NULL, 10);
    if(errno == ERANGE)
        driver.error(loc, "integer is out of range");
    return yy::lisplike_parser::make_NUMBER(val, loc);
    }
{lparen}        return yy::lisplike_parser::make_LPAREN(loc);
{rparen}        return yy::lisplike_parser::make_RPAREN(loc);
{squot}         return yy::lisplike_parser::make_SQUOT(loc);

.                 { driver.error(loc, "unexpected token"); }
%%

int yyFlexLexer::yylex()
{
    assert(false && "yyFlexLexer::yylex() called; this should not happen");
    return 0;
}

void lisplike_driver::scan_begin ()
{
    /*
    yy_flex_debug = trace_scanning;
    if (file.empty () || file == "-")
        yyin = stdin;
    else if (!(yyin = fopen (file.c_str (), "r")))
    {
        error ("cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
    */
}

void lisplike_driver::scan_end ()
{
    /*
    fclose (yyin);
    */
}

/*
int main(int, char **)
{
    //FlexLexer *lex = new yyFlexLexer();
    yyFlexLexer lex;
    lex.switch_streams(&std::cin, &std::cout);
    while(lex.yylex());
    return 0;
    
}
*/
#pragma clang diagnostic pop
