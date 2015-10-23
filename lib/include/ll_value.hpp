#ifndef LL_VALUE_HPP
#define LL_VALUE_HPP

#include <map>
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdint>
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
    dict,
    none
};

typedef const std::string& cstref;
//typedef std::shared_ptr<ll_value> ll_value_p;

class ll_value
{
public:
    typedef std::vector<ll_value> ll_value_list;
    typedef std::map<std::string, ll_value> ll_value_dict;

public:
    ll_value(const ll_value&) = default;
    ll_value(cstref val)
        : str_val(val)
        , type(ll_value_type::str) { }
    template<int sz>
    ll_value(const char (&val)[sz])
        : str_val(val)
        , type(ll_value_type::str) { }
    ll_value(double val)
        : real_val(val)
        , type(ll_value_type::real) { }
    ll_value(ll_value_list val)
        : list_val(val)
        , type(ll_value_type::list) { }
    ll_value(std::initializer_list<ll_value> list)
        : list_val(list)
        , type(ll_value_type::list) { }
    ll_value(ll_value_dict dict)
        : dict_val(dict)
        , type(ll_value_type::dict) { }
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

    int compare(const char *other) const
    {
        assert(type == ll_value_type::str && "tried to compare const char* and ll_value with non-str type");
        return str_val.compare(other);
    }

    ll_value& operator[](const std::string& index)
    {
        if(dict_val.count(index))
            return dict_val[index];
        else
        {
            dict_val[index] = ll_value();
            return dict_val[index];
        }
    }

    const ll_value& operator()() const
    {
        return *this;
    }

    explicit operator ll_value_list() const
        { return list_val; }

    explicit operator int8_t() const { return real_val; }
    explicit operator uint8_t() const { return real_val; }
    explicit operator int16_t() const { return real_val; }
    explicit operator uint16_t() const { return real_val; }
    explicit operator int32_t() const { return real_val; }
    explicit operator uint32_t() const { return real_val; }
    explicit operator int64_t() const { return real_val; }
    explicit operator uint64_t() const { return real_val; }

    explicit operator double() const
        { return real_val; }

    explicit operator cstref() const
        { return str_val; }

    /* values held by this class */
private:
    std::string str_val;
    double real_val;
    ll_value_list list_val;
    ll_value_dict dict_val;
    ll_value_type type;
private:
    friend bool isnone(const ll_value& val);
    friend bool operator== (const ll_value& left, const ll_value& right);
    friend ll_value operator%(const ll_value& left, int right);
    friend ll_value operator%(int left, const ll_value& right);
    friend ll_value operator+(const ll_value& left, double right);
    friend ll_value operator+(double left, const ll_value& right);
    friend ll_value operator+(const ll_value& left, const ll_value& right);
    friend ll_value operator-(const ll_value& left, double right);
    friend ll_value operator-(double left, const ll_value& right);
    friend ll_value operator-(const ll_value& left, const ll_value& right);
    friend ll_value operator*(const ll_value& left, double right);
    friend ll_value operator*(double left, const ll_value& right);
    friend ll_value operator*(const ll_value& left, const ll_value& right);
    friend ll_value operator/(const ll_value& left, double right);
    friend ll_value operator/(double left, const ll_value& right);
    friend ll_value operator/(const ll_value& left, const ll_value& right);
    friend std::ostream& operator<<(std::ostream& os, const ll_value& val);
};

typedef ll_value::ll_value_list ll_value_list;
typedef ll_value::ll_value_dict ll_value_dict;

inline bool isnone(const ll_value& val)
{
    return val.type == ll_value_type::none;
}

inline bool operator== (const ll_value& left, const ll_value& right)
{
    if(left.type != right.type)
        return false;
    else if(left.type == ll_value_type::none || right.type == ll_value_type::none)
        return false;
    else
        return left.compare(right) == 0;
}

inline ll_value operator%(const ll_value& left, int right)
{
    assert(left.type == ll_value_type::real && "tried to do % operation with a non real type");
    return static_cast<int>(left.real_val) % right;
}

inline ll_value operator%(int left, const ll_value& right)
{
    assert(right.type == ll_value_type::real && "tried to do % operation with a non real type");
    return left % static_cast<int>(right.real_val);
}

inline ll_value operator+(const ll_value& left, double right)
{
    assert(left.type == ll_value_type::real && "tried to do + operation with a non real type");
    return left.real_val + right;
}

inline ll_value operator+(double left, const ll_value& right)
{
    assert(right.type == ll_value_type::real && "tried to do + operation with a non real type");
    return left + right.real_val;
}

inline ll_value operator+(const ll_value& left, const ll_value& right)
{
    assert(left.type == ll_value_type::real && right.type == ll_value_type::real &&
            "tried to do + operation with a non real type");
    return left.real_val + right.real_val;
}

inline ll_value operator-(const ll_value& left, double right)
{
    assert(left.type == ll_value_type::real && "tried to do - operation with a non real type");
    return left.real_val - right;
}

inline ll_value operator-(double left, const ll_value& right)
{
    assert(right.type == ll_value_type::real && "tried to do - operation with a non real type");
    return left - right.real_val;
}

inline ll_value operator-(const ll_value& left, const ll_value& right)
{
    assert(left.type == ll_value_type::real && right.type == ll_value_type::real &&
            "tried to do - operation with a non real type");
    return left.real_val - right.real_val;
}

inline ll_value operator*(const ll_value& left, double right)
{
    assert(left.type == ll_value_type::real && "tried to do * operation with a non real type");
    return left.real_val * right;
}

inline ll_value operator*(double left, const ll_value& right)
{
    assert(right.type == ll_value_type::real && "tried to do * operation with a non real type");
    return left * right.real_val;
}

inline ll_value operator*(const ll_value& left, const ll_value& right)
{
    assert(left.type == ll_value_type::real && right.type == ll_value_type::real &&
            "tried to do * operation with a non real type");
    return left.real_val * right.real_val;
}

inline ll_value operator/(const ll_value& left, double right)
{
    assert(left.type == ll_value_type::real && "tried to do / operation with a non real type");
    return left.real_val / right;
}

inline ll_value operator/(double left, const ll_value& right)
{
    assert(right.type == ll_value_type::real && "tried to do / operation with a non real type");
    return left / right.real_val;
}

inline ll_value operator/(const ll_value& left, const ll_value& right)
{
    assert(left.type == ll_value_type::real && right.type == ll_value_type::real &&
            "tried to do / operation with a non real type");
    return left.real_val / right.real_val;
}

template<typename T>
inline bool operator== (const ll_value& left, const T& right)
    { return left.compare(right) == 0; }

template<typename T>
inline bool operator== (const T& left, const ll_value& right)
    { return right.compare(left) == 0; }

template<typename T>
inline bool operator<= (const ll_value& left, const T& right)
    { return left.compare(right) <= 0; }

template<typename T>
inline bool operator<= (const T& left, const ll_value& right)
    { return right.compare(left) > 0; }

template<typename T>
inline bool operator>= (const ll_value& left, const T& right)
    { return left.compare(right) >= 0; }

template<typename T>
inline bool operator>= (const T& left, const ll_value& right)
    { return right.compare(left) < 0; }

template<typename T>
inline bool operator< (const ll_value& left, const T& right)
    { return left.compare(right) < 0; }

template<typename T>
inline bool operator< (const T& left, const ll_value& right)
    { return right.compare(left) >= 0; }

template<typename T>
inline bool operator> (const ll_value& left, const T& right)
    { return left.compare(right) > 0; }

template<typename T>
inline bool operator> (const T& left, const ll_value& right)
    { return right.compare(left) <= 0; }

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
            os << "{ ";
            for(auto v : val.list_val)
            {
                if(v.type == ll_value_type::str)
                    os << "\"" << v << "\" ";
                else
                    os << v << " ";
            }
            os << "}";
            break;
        case ll_value_type::none:
            os << "none";
            break;
        default:
            assert(false && "unknown ll_value_type to convert to when outputting to ostream");
            break;
    }
    return os;
}

#endif
