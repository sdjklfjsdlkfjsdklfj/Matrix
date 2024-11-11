#include "matrix.h"
#include <iostream>
#include <utility>

math::Matrix::Matrix() : rows_(0), columns_(0), data_(std::make_unique<int[]>(0))
{
}

math::Matrix::Matrix(const Matrix& other) :
  rows_(other.rows_), columns_(other.columns_),
  data_(std::make_unique<int[]>(other.rows_ * other.columns_))
{
  for (size_t i = 0; i < rows_ * columns_; ++i) {
    data_[i] = other.data_[i];
  }
}

math::Matrix::Matrix(Matrix&& other) noexcept :
  rows_(other.rows_), columns_(other.columns_), data_(std::move(other.data_))
{
}

math::Matrix::Matrix(size_t rows, size_t columns) :
  rows_(rows), columns_(columns), data_(std::make_unique<int[]>(rows * columns))
{
}

math::Matrix::Matrix(size_t rows, size_t columns, int value) : Matrix(rows, columns)
{
  for (size_t i = 0; i < rows_ * columns_; ++i) {
    data_[i] = value;
  }
}

math::Matrix& math::Matrix::operator=(const Matrix& rhs)
{
  if (this != &rhs) {
    Matrix tmp(rhs);
    std::swap(*this, tmp);
  }
  return *this;
}

math::Matrix& math::Matrix::operator=(Matrix&& rhs) noexcept
{
  if (this != &rhs) {
    rows_ = std::exchange(rhs.rows_, 0);
    columns_ = std::exchange(rhs.columns_, 0);
    data_ = std::move(rhs.data_);
  }
  return *this;
}

int* math::Matrix::operator[](size_t index)
{
  return data_.get() + index * columns_;
}

const int* math::Matrix::operator[](size_t index) const
{
  return data_.get() + index * columns_;
}

size_t math::Matrix::getRows() const noexcept
{
  return rows_;
}

size_t math::Matrix::getColumns() const noexcept
{
  return columns_;
}

void math::Matrix::resize(size_t rows, size_t columns)
{
  if (rows == rows_ && columns == columns_) {
    return;
  }
  Matrix tmp(rows, columns);
  size_t sharedRows = std::min(rows, rows_);
  size_t sharedColumns = std::min(columns, columns_);
  for (size_t i = 0; i < sharedRows; ++i) {
    for (size_t j = 0; j < sharedColumns; ++j) {
      tmp.data_[i * tmp.columns_ + j] = data_[i * columns_ + j];
    }
  }
  *this = std::move(tmp);
}

void math::Matrix::fill(int value)
{
  for (size_t i = 0; i < rows_ * columns_; ++i) {
    data_[i] = value;
  }
}

void math::Matrix::clear() noexcept
{
  data_.reset();
  rows_ = 0;
  columns_ = 0;
}

std::istream& operator>>(std::istream& is, math::Matrix& matrix)
{
  for (size_t i = 0; i < matrix.getRows(); ++i) {
    for (size_t j = 0; j < matrix.getColumns(); ++j) {
      is >> matrix[i][j];
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const math::Matrix& matrix)
{
  for (size_t i = 0; i < matrix.getRows(); ++i) {
    os << matrix[i][0];
    for (size_t j = 1; j < matrix.getColumns(); ++j) {
      os << ' ' << matrix[i][j];
    }
    if (i < matrix.getRows() - 1) {
      os << '\n';
    }
  }
  return os;
}
