#include "matrix.h"
#include <algorithm>

Matrix::Matrix() : rows_(0), columns_(0), data_(std::make_unique<int[]>(0))
{
}

Matrix::Matrix(const Matrix& other) :
  rows_(other.rows_), columns_(other.columns_),
  data_(std::make_unique<int[]>(other.rows_ * other.columns_))
{
  std::copy_n(other.data_.get(), other.rows_ * other.columns_, data_.get());
}

Matrix::Matrix(Matrix&& other) noexcept :
  rows_(other.rows_), columns_(other.columns_), data_(std::move(other.data_))
{
}

Matrix::Matrix(size_t rows, size_t columns) :
  rows_(rows), columns_(columns), data_(std::make_unique<int[]>(rows * columns))
{
}

Matrix::Matrix(size_t rows, size_t columns, int value) : Matrix(rows, columns)
{
  std::fill_n(data_.get(), rows * columns, value);
}

Matrix& Matrix::operator=(const Matrix& other)
{
  if (this != &other) {
    Matrix tmp(other);
    swap(tmp);
  }
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
  if (this != &other) {
    swap(other);
  }
  return *this;
}

int* Matrix::operator[](size_t index)
{
  return data_.get() + index * columns_;
}

const int* Matrix::operator[](size_t index) const
{
  return data_.get() + index * columns_;
}

int& Matrix::at(size_t row, size_t column)
{
  if (row >= rows_ || column >= columns_) {
    throw std::out_of_range("Row or column out of range");
  }
  return *(data_.get() + row * columns_ + column);
}

const int& Matrix::at(size_t row, size_t column) const
{
  if (row >= rows_ || column >= columns_) {
    throw std::out_of_range("Row or column out of range");
  }
  return *(data_.get() + row * columns_ + column);
}

size_t Matrix::getRows() const noexcept
{
  return rows_;
}

size_t Matrix::getColumns() const noexcept
{
  return columns_;
}

std::istream& Matrix::input(std::istream& is)
{
  for (size_t i = 0; i < rows_ * columns_; ++i) {
    is >> data_[i];
  }
  return is;
}

std::ostream& Matrix::output(std::ostream& os) const
{
  for (size_t i = 0; i < rows_ * columns_; i += columns_) {
    os << data_[i];
    for (size_t j = 1; j < columns_; ++j) {
      os << ' ' << data_[i + j];
    }
    os << '\n';
  }
  return os;
}

void Matrix::resize(size_t rows, size_t columns)
{
  if (rows == rows_ && columns == columns_) {
    return;
  }
  Matrix tmp(rows, columns);

  size_t sharedRows = std::min(rows, rows_);
  size_t sharedColumns = std::min(columns, columns_);
  for (size_t i = 0; i < sharedRows; ++i) {
    for (size_t j = 0; j < sharedColumns; ++j) {
      size_t indexNew = i * columns + j;
      size_t indexOld = i * columns_ + j;
      tmp.data_[indexNew] = data_[indexOld];
    }
  }
  swap(tmp);
}

void Matrix::fill(int value)
{
  std::fill(data_.get(), data_.get() + rows_ * columns_, value);
}

void Matrix::clear() noexcept
{
  data_.reset();
  rows_ = 0;
  columns_ = 0;
}

void Matrix::swap(Matrix& other)
{
  std::swap(rows_, other.rows_);
  std::swap(columns_, other.columns_);
  std::swap(data_, other.data_);
}

