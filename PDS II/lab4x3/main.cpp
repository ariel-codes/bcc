#include "Matrix.hpp"
#include "Operations.hpp"
#include <iostream>
#include <vector>

int main() {
  int row, col, input, num = 0, repetitions;
  std::string op;
  std::vector<int> values;
  std::vector<Matrix> matrices;
  Operations oper = Operations();
  std::cin >> repetitions;
  while (num < repetitions) {
    int i = 0;
    matrices.clear();
    while (i < 2) {
      values.clear();
      std::cin >> row >> col;
      for (int i = 0; i < row * col; i++) {
        std::cin >> input;
        values.push_back(input);
      }
      Matrix m = Matrix(row, col);
      m.buildMatrix(values);
      matrices.push_back(m);
      i++;
    }
    try {
      std::cin >> op;
      if (op == "*") {
        oper.multiply(matrices[0], matrices[1]);
      } else if (op == "+") {
        oper.add(matrices[0], matrices[1]);
      }
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
    num++;
  }
  return 0;
}