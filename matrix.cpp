#include "matrix.h"
#include <cmath>
#include <stdexcept>

Matrix::Matrix(const Matrix& other) :
  rows_(other.rows_), columns_(other.columns_), size_(other.size_),
  data_(other.size_ ? new int[other.size_] : nullptr),
  is_initialized_(other.is_initialized_)
{
  if (is_initialized_) {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }
}

Matrix::Matrix(Matrix&& other) noexcept :
  rows_(other.rows_), columns_(other.columns_), size_(other.size_),
  data_(other.data_), is_initialized_(other.is_initialized_)
{
  other.reset();
}

Matrix::Matrix(size_t rows, size_t columns) :
  rows_(rows), columns_(columns), size_(rows * columns), data_(nullptr),
  is_initialized_(false)
{
  checkSizes(rows, columns);
  data_ = new int[size_];
}

Matrix::Matrix(size_t rows, size_t columns, int value) : Matrix(rows, columns)
{
  is_initialized_ = true;
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

Matrix::~Matrix() noexcept
{
  delete[] data_;
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
  return data_ + index * columns_;
}

const int* Matrix::operator[](size_t index) const
{
  return data_ + index * columns_;
}

int& Matrix::at(size_t row, size_t column)
{
  checkBounds(row, column);
  checkIsInitialized();
  return *(data_ + row * columns_ + column);
}

const int& Matrix::at(size_t row, size_t column) const
{
  checkBounds(row, column);
  checkIsInitialized();
  return *(data_ + row * columns_ + column);
}

size_t Matrix::rows() const noexcept
{
  return rows_;
}

size_t Matrix::columns() const noexcept
{
  return columns_;
}

void Matrix::input(std::istream& is)
{
  checkIsEmpty();
  for (size_t i = 0; i < size_; ++i) {
    is >> data_[i];
  }
  is_initialized_ = !is.bad();
}

void Matrix::output(std::ostream& os) const
{
  checkIsInitialized();
  for (size_t i = 0; i < size_; i += columns_) {
    os << data_[i];
    for (size_t j = 1; j < columns_; ++j) {
      os << ' ' << data_[i + j];
    }
    os << '\n';
  }
}

void Matrix::resize(size_t rows, size_t columns)
{
  checkSizes(rows, columns);
  if (rows == rows_ && columns == columns_) {
    return;
  }
  Matrix tmp(rows, columns);

  if (!is_initialized_) {
    swap(tmp);
    return;
  }
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < columns; ++j) {
      bool isValid = i < rows_ && j < columns_;
      size_t indexNew = i * columns + j;
      size_t indexOld = i * columns_ + j;
      tmp.data_[indexNew] = isValid ? data_[indexOld] : int();
    }
  }
  tmp.is_initialized_ = true;
  swap(tmp);
}

void Matrix::fill(int value)
{
  checkIsEmpty();
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

void Matrix::clear() noexcept
{
  delete[] data_;
  reset();
}

void Matrix::swap(Matrix& other)
{
  std::swap(rows_, other.rows_);
  std::swap(columns_, other.columns_);
  std::swap(size_, other.size_);
  std::swap(data_, other.data_);
  std::swap(is_initialized_, other.is_initialized_);
}

void Matrix::reset()
{
  data_ = nullptr;
  rows_ = 0;
  columns_ = 0;
  size_ = 0;
  is_initialized_ = false;
}

void Matrix::checkBounds(size_t row, size_t column) const
{
  if (row >= rows_ || column >= columns_) {
    throw std::out_of_range("Row or column out of range");
  }
}

void Matrix::checkSizes(size_t rows, size_t columns) const
{
  if (rows <= 0 || columns <= 0) {
    throw std::logic_error("Rows/columns must be greater than zero");
  }
}

void Matrix::checkIsInitialized() const
{
  if (!is_initialized_) {
    throw std::logic_error("Not initialized matrix");
  }
}

void Matrix::checkIsEmpty() const
{
  if (data_ == nullptr) {
    throw std::logic_error("Empty matrix");
  }
}
