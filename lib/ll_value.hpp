#ifndef LL_VALUE_HPP
#define LL_VALUE_HPP

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>

/*
 * This file is a representation of a Lisp-Like value. It's designed to be
 * dynamically assigned, so while it may hold many values at once, it only has
 * one interpreted value that can be used.
 *
 * Mixing and matching will come later.
 */

enum class ll_value_type
{
    str,
    real,
    fun,
    list,
    none
};

class ll_value;

typedef const std::string& cstref;
typedef std::shared_ptr<ll_value> ll_value_p;
typedef std::vector<ll_value_p> ll_value_list;

class ll_value
{
public:
    ll_value(cstref val)
        : str_val(val)
        , type(ll_value_type::str) { }
    ll_value(const char *val)
        : str_val(val)
        , type(ll_value_type::str) { }
    ll_value(double val)
        : real_val(val)
        , type(ll_value_type::real) { }
    ll_value(ll_value_list val)
        : list_val(val)
        , type(ll_value_type::list) { }
    ll_value()
        : type(ll_value_type::none) { }

public:
    template<typename T>
    int compare(T other) const;

    int compare(const ll_value& other) const
    {
        switch(type)
        {
            case ll_value_type::str:
                return str_val.compare(other.str_val);
            case ll_value_type::real:
                if(real_val < other.real_val) return -1;
                else if(real_val > other.real_val) return 1;
                else return 0;
            case ll_value_type::list:
                if(list_val.size() < other.list_val.size())
                    return -1;
                else if(list_val.size() > other.list_val.size())
                    return 1;
                else
                    return !(std::equal(list_val.begin(), list_val.end(), other.list_val.begin()));
            default:
                assert(false && "unknown ll_value type");
                return 1;
        }
    }

    int compare(int other) const
        { return (real_val - other); }

    operator double() const
    {
        assert(type == ll_value_type::real
            && "tried to coerce a double into some other type"); 
        return real_val;
    }

    operator const char*() const
    {
        assert(type == ll_value_type::str
            && "tried to coerce a string into some other type"); 
        return str_val.c_str();
    }

    operator const std::string&() const
    {
        assert(type == ll_value_type::str
            && "tried to coerce a string into some other type"); 
        return str_val;
    }

public:
    std::string str_val;
    double real_val;
    ll_value_list list_val;
    ll_value_type type;
};

inline bool operator== (const ll_value& left, const ll_value& right)
{
    if(left.type != right.type)
        return false;
    else
        return left.compare(right) == 0;
}

template<typename T>
inline bool operator== (const ll_value& left, const T& right)
    { return left.compare(right) == 0.0; }

template <typename ... T>
inline void print(const std::string& f, const T& ... tail)
{
    std::cout << fmt(f, tail ...);
}

template <typename ... T>
inline std::string fmt(const std::string& f, const T& ...);

template <typename ... T>
inline std::string fmt(const std::string& f)
{
    return f;
}

template <typename Head, typename ... Tail>
inline std::string fmt(const std::string& f, const Head& head, 
    const Tail& ... tail)
{
    const std::string placeholder("%");

    std::stringstream os;
    size_t placeholderPos = f.find(placeholder);

    if(placeholderPos == std::string::npos)
        return f;
    else
    {
        std::string front(f, 0, placeholderPos);
        std::string back(f, placeholderPos + placeholder.size());

        os << front << head << fmt(back, tail ...);
    }

    return os.str();
}

inline std::ostream& operator<<(std::ostream& os, const ll_value& val)
{
    switch(val.type)
    {
        case ll_value_type::str:
            os << val.str_val;
            break;
        case ll_value_type::real:
            os << val.real_val;
            break;
        case ll_value_type::list:
            // TODO
            os << "- LIST VALUE -";
            break;
        default:
            assert(false && "unknown ll_value_type to convert to when outputting to ostream");
            break;
    }
    return os;
}

#endif