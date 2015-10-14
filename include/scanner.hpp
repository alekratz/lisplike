#ifndef SCANNER_HPP
#define SCANNER_HPP

//#include <FlexLexer.h>
#include "driver.hpp"
#include "parser.hpp"

#ifndef __FLEX_LEXER_H
#define yyFlexLexer yyFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

#define YY_DECL \
    yy::lisplike_parser::symbol_type lisplike_scanner::lex(lisplike_driver& driver)
#define yyterminate() return yy::lisplike_parser::make_END(loc);

class yyFlexLexer;

class lisplike_scanner
    : public yyFlexLexer
{
public:
    lisplike_scanner(std::istream *in = nullptr, std::ostream *out = nullptr)
        : yyFlexLexer(in, out)
    { }

public:
    yy::lisplike_parser::symbol_type lex(lisplike_driver& driver);

protected:
    //lisplike_driver& driver;
};

#endif /* SCANNER_HPP */