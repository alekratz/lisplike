#ifndef LL_TYPE_HPP
#define LL_TYPE_HPP

#include <string>
#include <vector>
#include <memory>
//#include <unordered_map>
#include <sstream>
#include <cstdint>
#include <cassert>
#include "util.hpp"

enum class ll_type
{
    str,
    real,
    list,
    dict,
    none,
};


/**
 * @brief ll_line class
 */
class ll_line
{
public:

    ll_line() = default;
    virtual ~ll_line() = default;

    /* operations */
public:
    virtual std::string gencode() = 0;
};

typedef std::shared_ptr<ll_line> ll_line_p;
typedef std::vector<ll_line_p> ll_line_vec;

class ll_none :
    public ll_line
{
public:
    ll_none() = default;
    virtual ~ll_none() = default;
public:
    virtual std::string gencode() { return "None"; };
};

class ll_value :
    public ll_line
{
public:
    ll_value(double val) 
        : real_val(val)
        , type(ll_type::real) { }
    ll_value(cstref val)
        : str_val(val)
        , type(ll_type::str) { }
    ll_value(const char *val)
        : str_val(val)
        , type(ll_type::str) { }
    ll_value(const ll_line_vec& val)
        : list_val(val)
        , type(ll_type::list) { }

    virtual ~ll_value() = default;
public:
    virtual std::string gencode();
    ll_type get_type() { return type; }

private:
    double real_val;
    std::string str_val;
    ll_line_vec list_val;
    ll_type type;
};

class ll_fundecl :
    public ll_line
{
public:
    ll_fundecl(cstref identifier, ll_line_p args, const ll_line_vec& lines)
        : identifier(identifier)
        , args(args)
        , lines(lines)
    {
        assert(dynamic_cast<ll_value*>(args.get())->get_type() == ll_type::list && "args must be a list");
    }

    virtual std::string gencode();

private:
    std::string identifier;
    ll_line_p args;
    ll_line_vec lines;
};

class ll_funcall :
    public ll_line
{
public:
    ll_funcall(cstref identifier, const ll_line_vec& params)
    : identifier(identifier)
    , params(params) { }

public:
    virtual std::string gencode();

private:
    std::string identifier;
    ll_line_vec params;
};

/*
 * TODO : maybe rename this to lisplike_term? or ll_term?
 * TODO : maybe make this a ll_line class that records functions, function calls, and function declarations?
 */

class ll_let
    : public ll_line
{
public:
    ll_let(const std::string& identifier, ll_line_p value)
        : identifier(identifier)
        , value(value) { }

public:
    virtual std::string gencode();

private:
    std::string identifier;
    ll_line_p value;
};


/* ostream definitions */
std::ostream& operator<<(std::ostream& os, const ll_line_p& ll_val);
std::ostream& operator<<(std::ostream& os, const ll_line_vec& ll_vals);

#endif /* LL_TYPE_HPP */
