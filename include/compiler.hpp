#ifndef COMPILER_HPP
#define COMPILER_HPP

class lisplike_compiler
{
public:
  lisplike_compiler();
  virtual ~lisplike_compiler() = default;

public:
  std::string compile(const std::string input_text);
};

#endif
