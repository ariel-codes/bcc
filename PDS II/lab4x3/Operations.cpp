#include "Operations.hpp"
#include <sstream>

void Operations::add(Matrix m1, Matrix m2) {
  const int rows = m1.getRow();
  const int cols = m1.getCol();

  if (rows != m2.getRow() || cols != m2.getCol()) {
    throw AddError(m1, m2);
  }

  Matrix res(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      res.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
  res.showMatrix();
}

void Operations::multiply(Matrix m1, Matrix m2) {
  if (m2.getRow() != m1.getCol()) {
    throw MultiplyError(m1, m2);
  }

  Matrix res(m1.getRow(), m2.getCol());
  for (int i = 0; i < m1.getRow(); i++)
    for (int j = 0; j < m2.getCol(); j++)
      for (int k = 0; k < m1.getCol(); k++)
        res.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
  res.showMatrix();
}

Operations::AddError::AddError(Matrix m1, Matrix m2) {
  std::ostringstream reason_s;
  reason_s << "ERROR (ADD): Both dimensions must agree. (" << m1.getRow() << ','
           << m1.getCol() << ") != (" << m2.getCol() << ',' << m2.getCol()
           << ')';
  reason = reason_s.str();
}
Operations::MultiplyError::MultiplyError(Matrix m1, Matrix m2) {
  std::ostringstream reason_s;
  reason_s << "ERROR (MULTIPLY): Number of columns of first matrix must agree "
              "with number of rows of second matrix. ("
           << m1.getCol() << ") != (" << m2.getRow() << ')';
  reason = reason_s.str();
}
const char *Operations::Error::what() const noexcept {
  return this->reason.c_str();
}