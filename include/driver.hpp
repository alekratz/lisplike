#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <string>
#include <unordered_map>
#include <iostream>
#include "parser.hpp"

extern bool verbose;
/* Verbose CERR */
#define VCERR if(verbose) std::cerr

class lisplike_scanner;

class lisplike_driver
{
public:
    lisplike_driver();
    virtual ~lisplike_driver();

    /* operations */
public:
    void scan_begin();
    void scan_end();

    bool parse_stream(std::istream& in, const std::string& sname, std::ostream& out=std::cout);
    bool parse_string(const std::string& line, const std::string& sname, std::ostream& out=std::cout);
    bool parse_file(const std::string& f, std::ostream& out=std::cout);
    

    void error (const yy::location& l, const std::string& m);
    void error (const std::string& m);

    /* members */
public:
    std::unordered_map<std::string, int> variables;
    std::string streamname;
    
    bool trace_scanning;
    bool trace_parsing;
    int result;
    ll_children ast;

    lisplike_scanner* lexer;
};

#endif /* DRIVER_HPP */