#include "Matrix.hpp"

Matrix::Matrix(int rows, int columns) : row(rows), col(columns) {
  matrix = std::vector<std::vector<int>>(rows, std::vector<int>(columns, 0));
}

int Matrix::getRow() { return this->row; }
int Matrix::getCol() { return this->col; }
std::vector<std::vector<int>> Matrix::getMatrix() { return this->matrix; }

void Matrix::buildMatrix(std::vector<int> values) {
  std::vector<int>::iterator iter = values.begin();
  for (int i = 0; i < this->row; i++)
    for (int j = 0; j < this->col; j++) {
      this->matrix[i][j] = *iter;
      ++iter;
    }
}

void Matrix::showMatrix() {
  for (auto &&rows : this->matrix) {
    for (auto &&value : rows)
      std::cout << value << ' ';
    std::cout << '\n';
  }
  std::cout << std::endl;
}

void Matrix::setMatrix(std::vector<std::vector<int>> new_matrix) {
  this->matrix = new_matrix;
}