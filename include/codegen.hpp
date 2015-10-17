#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include "ast.hpp"
#include "driver.hpp"

std::string gen_header(const lisplike_driver& driver);
std::string gen_cpp(const lisplike_driver& driver);
std::string gen_main(const lisplike_driver& driver);

#endif