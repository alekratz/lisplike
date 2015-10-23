#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include "ast.hpp"
#include "driver.hpp"

std::string genheader(const lisplike_driver& driver);
std::string gencpp(const lisplike_driver& driver);
std::string genmain(const lisplike_driver& driver);

#endif