#ifndef LL_HPP
#define LL_HPP

#include "ll_value.hpp"
#include "ll_util.hpp"

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

template <typename ... T>
inline ll_value println(const std::string& f, const T& ... tail)
{
    std::cout << fmt(f, tail ...) << std::endl;
    return ll_value();
}

template <typename ... T>
inline ll_value print(const std::string& f, const T& ... tail)
{
    std::cout << fmt(f, tail ...);
    return ll_value();
}

#endif