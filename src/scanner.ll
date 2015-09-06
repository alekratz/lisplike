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

// Location of the current token
static yy::location loc;

#define YY_USER_ACTION loc.columns(yyleng);

# undef yywrap
# define yywrap() 1

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-register"
%}

string    \"[^\n]*\" /*" /**/
ws        [\t ]
alpha     [a-zA-Z]
dig       [0-9]

ident     ({alpha}|_)({alpha}|_|{dig})*
num       {dig}+

lparen    \(
rparen    \)

%%

%{
// call this every time yylex is called
loc.step();
%}

{ws}      loc.step();
{ident}   return yy::lisplike_parser::make_IDENTIFIER(yytext, loc);
{num}     {
  errno = 0;
  int64_t val = strtol(yytext, NULL, 10);
  if(errno == ERANGE)
    driver.error(loc, "integer is out of range");
  return yy::lisplike_parser::make_NUMBER(val, loc);
}
{lparen}  return yy::lisplike_parser::make_LPAREN(loc);
{rparen}  return yy::lisplike_parser::make_RPAREN(loc);
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