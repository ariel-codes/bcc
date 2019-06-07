#include <string>

using std::string;

class TriangularNumber {
public:
  static int getElement(int);
  static string draw(int);
};

class InvalidTriangularNumber : std::exception {
  using std::exception::exception;
};
