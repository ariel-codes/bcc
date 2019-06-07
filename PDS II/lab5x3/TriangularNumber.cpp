#include "TriangularNumber.hpp"

int TriangularNumber::getElement(int T) {
  if (T < 0) {
    throw InvalidTriangularNumber();
  }
  const int x = T * (T + 1);
  if (T != 0 && x / T != (T + 1)) {
    throw InvalidTriangularNumber();
  }
  return x / 2;
}

string TriangularNumber::draw(int T) {
  if (T < 0) {
    throw InvalidTriangularNumber();
  }
  if (T != 0 && T * (T + 1) / T != (T + 1)) {
    throw InvalidTriangularNumber();
  }
  string out = "";
  for (int i = 1; i <= T; i++) {
    out.insert(out.end(), i, '*');
    if (i > 0 && i != T) {
      out.append("\n");
    }
  }
  return out;
}