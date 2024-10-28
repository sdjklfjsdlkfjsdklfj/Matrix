#include "matrix.h"
#include <utility>

Matrix::Matrix(const Matrix& other) :
  rows_(other.rows_), columns_(other.columns_), size_(other.size_),
  data_(new value_type[other.size_])
{
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

Matrix::Matrix(Matrix&& other) noexcept :
  rows_(other.rows_), columns_(other.columns_), size_(other.size_),
  data_(other.data_)
{
  other.rows_ = 0;
  other.columns_ = 0;
  other.size_ = 0;
  other.data_ = nullptr;
}

Matrix::Matrix(size_type rows, size_type columns) :
  rows_(rows), columns_(columns), size_(rows * columns), data_()
{
  checkSize(rows_, columns_);
  data_ = new value_type[size_];
}

Matrix::Matrix(size_type rows, size_type columns, value_type value) :
  Matrix(rows, columns)
{
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

Matrix::~Matrix() noexcept
{
  delete[] data_;
}

Matrix& Matrix::operator=(const Matrix& other)
{
  if (this == &other) {
    return *this;
  }
  delete[] data_;
  rows_ = other.rows_;
  columns_ = other.columns_;
  size_ = other.size_;
  data_ = new value_type[size_];
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
  if (this == &other) {
    return *this;
  }
  std::swap(rows_, other.rows_);
  std::swap(columns_, other.columns_);
  std::swap(size_, other.size_);
  std::swap(data_, other.data_);
  return *this;
}
