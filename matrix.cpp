#include "matrix.h"

int** createMatrix(const size_t rows, const size_t columns) {
  int** matrix = new int*[rows];
  size_t createdRows = 0;
  try {
    for (; createdRows < rows; ++createdRows) {
      matrix[createdRows] = new int[columns];
    }
  } catch (const std::bad_alloc& e) {
    deleteMatrix(matrix, createdRows);
    throw;
  }
  return matrix;
}

void deleteMatrix(int* const* matrix, const size_t rows) {
  for (size_t i = 0; i < rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void inputMatrix(std::istream& is,
                 int* const* matrix,
                 const size_t rows,
                 const size_t columns) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < columns; ++j)
      is >> matrix[i][j];
  }
}

void outputMatrix(std::ostream& os,
                  const int* const* matrix,
                  const size_t rows,
                  const size_t columns) {
  for (size_t i = 0; i < rows; ++i) {
    os << matrix[i][0];
    for (size_t j = 1; j < columns; ++j)
      os << ' ' << matrix[i][j];
    os << '\n';
  }
}
