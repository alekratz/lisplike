#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

typedef const std::string& cstref;

#include "ast.hpp"

std::string pad_internal(const ll_children& terms, cstref inner);

#endif
