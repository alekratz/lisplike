#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include <algorithm> 
#include <functional>
#include <cctype>
#include <boost/filesystem.hpp>

typedef const std::string& cstref;

#include "ast.hpp"

std::string pad_internal(const ll_children& terms, cstref inner);
bool create_directory_tree(const boost::filesystem::path& path);

// Character predicate type
typedef std::function<int(int)> char_pred_t;

// Shamelessly stolen from stackoverflow
// trim from start
inline std::string &ltrim(std::string &s, char_pred_t splitwith=(int(*)(int))&std::isspace) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(splitwith)));
        return s;
}

// trim from end
inline std::string &rtrim(std::string &s, char_pred_t splitwith=(int(*)(int))&std::isspace) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(splitwith)).base(), s.end());
        return s;
}

// trim from both ends
inline std::string &trim(std::string &s, char_pred_t splitwith=(int(*)(int))&std::isspace) {
        return ltrim(rtrim(s, splitwith), splitwith);
}

#endif
