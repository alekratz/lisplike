#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include "ast.hpp"

std::string gen_header(const ll_children& tree);
std::string gen_cpp(const ll_children& tree);
std::string gen_main(const ll_children& tree);

#endif