#include "matrix.h"
#include <stdexcept>

Matrix::Matrix(const Matrix& other) :
  rows_(other.rows_), columns_(other.columns_), size_(other.size_),
  data_(other.size_ ? new value_type[other.size_] : nullptr),
  is_initialized_(other.is_initialized_)
{
  if (is_initialized_) {
    for (size_type i = 0; i < size_; ++i) {
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

Matrix::Matrix(size_type rows, size_type columns) :
  rows_(rows), columns_(columns), size_(rows * columns), data_(nullptr),
  is_initialized_(false)
{
  if (rows <= 0 || columns <= 0) {
    throw std::logic_error("Rows/columns must be greater than zero");
  }
  data_ = new value_type[size_];
}

Matrix::Matrix(size_type rows, size_type columns, value_type value) :
  Matrix(rows, columns)
{
  is_initialized_ = true;
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

Matrix::value_type* Matrix::operator[](size_type index)
{
  return data_ + index * columns_;
}

const Matrix::value_type* Matrix::operator[](size_type index) const
{
  return data_ + index * columns_;
}

Matrix::reference Matrix::at(size_type row, size_type column)
{
  checkBounds(row, column);
  checkIsInitialized();
  return *(data_ + row * columns_ + column);
}

Matrix::const_reference Matrix::at(size_type row, size_type column) const
{
  checkBounds(row, column);
  checkIsInitialized();
  return *(data_ + row * columns_ + column);
}

Matrix::size_type Matrix::rows() const noexcept
{
  return rows_;
}

Matrix::size_type Matrix::columns() const noexcept
{
  return columns_;
}

void Matrix::input(std::istream& is)
{
  checkIsEmpty();
  for (size_type i = 0; i < size_; ++i) {
    is >> data_[i];
  }
  is_initialized_ = !is.bad();
}

void Matrix::output(std::ostream& os) const
{
  checkIsInitialized();
  for (size_type i = 0; i < size_; i += columns_) {
    os << data_[i];
    for (size_type j = 1; j < columns_; ++j) {
      os << ' ' << data_[i + j];
    }
    os << '\n';
  }
}

void Matrix::resize(size_type rows, size_type columns)
{
  if (rows <= rows_ || columns <= columns_) {
    const char* message = "New rows and columns must be greater than existing";
    throw std::invalid_argument(message);
  }
  value_type* tmp = new value_type[rows * columns];
  if (is_initialized_) {
    for (size_type i = 0; i < size_; i += columns_) {
      for (size_type j = 0; j < columns_; ++j) {
        tmp[i + j] = data_[i + j];
      }
    }
  }
  clear();
  data_ = tmp;
  rows_ = rows;
  columns_ = columns;
  size_ = rows * columns;
}

void Matrix::fill(value_type value)
{
  checkIsEmpty();
  for (size_type i = 0; i < size_; ++i) {
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

void Matrix::checkBounds(size_type row, size_type column) const
{
  if (row >= rows_ || column >= columns_) {
    throw std::out_of_range("Row or column out of range");
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
