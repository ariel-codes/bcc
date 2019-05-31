#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "Matrix.hpp"
#include <string>

class Operations {
public:
  void add(Matrix, Matrix);
  void multiply(Matrix, Matrix);

  class Error : public std::exception {
  public:
    std::string reason;
    const char *what() const noexcept;
  };
  class AddError : public Error {
  public:
    AddError(Matrix, Matrix);
  };
  class MultiplyError : public Error {
  public:
    MultiplyError(Matrix, Matrix);
  };
};

#endif