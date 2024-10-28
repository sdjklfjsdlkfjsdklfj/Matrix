#include "matrix.h"
#include <stdexcept>
#include <utility>

Matrix::Matrix(const Matrix& other) :
  rows_(other.rows_), columns_(other.columns_), size_(other.size_),
  data_(new value_type[other.size_])
{
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  } } Matrix::Matrix(Matrix&& other) noexcept :
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
  swap(other);
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
  if (row >= rows_ || column >= columns_) {
    throw std::out_of_range("Row or column out of range");
  }
  return *(data_ + row*columns_ + column);
}

Matrix::const_reference Matrix::at(size_type row, size_type column) const
{
  if (row >= rows_ || column >= columns_) {
    throw std::out_of_range("Row or column out of range");
  }
  return *(data_ + row*columns_ + column);
}

Matrix::size_type Matrix::getRows() const noexcept
{
  return rows_;
}

Matrix::size_type Matrix::getColumns() const noexcept
{
  return columns_;
}

Matrix::value_type Matrix::getMinimum() const
{
  if (data_ == nullptr) {
    throw std::logic_error("Empty matrix");
  }
  value_type minimum = *data_;
  for (size_type i = 1; i < size_; ++i) {
    if (data_[i] < minimum) {
      minimum = data_[i];
    }
  }
  return minimum;
}

Matrix::value_type Matrix::getMaximum() const
{
  if (data_ == nullptr) {
    throw std::logic_error("Empty matrix");
  }
  value_type maximum = *data_;
  for (size_type i = 1; i < size_; ++i) {
    if (data_[i] > maximum) {
      maximum = data_[i];
    }
  }
  return maximum;
}

Matrix::value_type Matrix::getSum() const
{
  if (data_ == nullptr) {
    throw std::logic_error("Empty matrix");
  }
  value_type sum = *data_;
  for (size_type i = 1; i < size_; ++i) {
    sum += data_[i];
  }
  return sum;
}

Matrix::value_type Matrix::getAverage() const
{
  value_type sum = getSum();
  return sum / size_;
}

void Matrix::input(std::istream& is)
{
  if (data_ == nullptr) {
    throw std::logic_error("Empty matrix");
  }
  for (size_type i = 0; i < size_; ++i) {
    is >> data_[i];
  }
}

void Matrix::output(std::ostream& os) const
{
  if (data_ == nullptr) {
    throw std::logic_error("Empty matrix");
  }
  for (size_type i = 0; i < size_; i += columns_) {
    os << data_[i];
    for (size_type j = 1; j < columns_; ++j) {
      os << ' ' << data_[i + j];
    }
    os << '\n';
  }
}

// void Matrix::resize(size_type rows, size_type columns)
//{
// if (rows <= rows_ || columns <= columns_) {
// const char* message = "New rows and columns must be greater than existing";
// throw std::invalid_argument(message);
//}
// value_type* tmp = new value_type[rows * columns];
//}

void Matrix::fill(value_type value)
{
  if (data_ == nullptr) {
    throw std::logic_error("Empty matrix");
  }
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

void Matrix::clear() noexcept
{
  delete[] data_;
  data_ = nullptr;
  rows_ = 0;
  columns_ = 0;
  size_ = 0;
}

void Matrix::swap(Matrix& other)
{
  std::swap(rows_, other.rows_);
  std::swap(columns_, other.columns_);
  std::swap(size_, other.size_);
  std::swap(data_, other.data_);
}

void Matrix::checkSize(size_type rows, size_type columns) const
{
  if (rows <= 0 || columns <= 0) {
    throw std::logic_error("Rows/columns must be greater than zero");
  }
}
