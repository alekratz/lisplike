#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <iostream>
#include <string>
#include <sstream>

template <typename ... T>
std::string format(const std::string& fmt, const T& ...);

template <typename ... T>
std::string format(const std::string& fmt)
{
    return fmt;
}

template <typename Head, typename ... Tail>
std::string format(const std::string& fmt, const Head& head, 
    const Tail& ... tail)
{
    const std::string placeholder("%");

    std::stringstream os;
    size_t placeholderPos = fmt.find(placeholder);

    if(placeholderPos == std::string::npos)
        return fmt;
    else
    {
        std::string front(fmt, 0, placeholderPos);
        std::string back(fmt, placeholderPos + placeholder.size());

        os << front << head << format(back, tail ...);
    }

    return os.str();
}

#endif

