#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

class Matrix {
private:
  int row, col;
  std::vector<std::vector<int>> matrix;

  friend class Operations;

public:
  void buildMatrix(std::vector<int>);
  Matrix(int, int);
  int getRow();
  int getCol();
  std::vector<std::vector<int>> getMatrix();
  void showMatrix();
  void setMatrix(std::vector<std::vector<int>>);
};

#endif