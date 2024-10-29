#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
public:
  using size_type = std::size_t;
  using value_type = int;
  using reference = value_type&;
  using const_reference = const value_type&;

  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;
  explicit Matrix(size_type, size_type);
  explicit Matrix(size_type, size_type, value_type);
  ~Matrix() noexcept;

  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&& other) noexcept;

  value_type* operator[](size_type);
  const value_type* operator[](size_type) const;

  const_reference at(size_type, size_type) const;
  reference at(size_type, size_type);

  size_type rows() const noexcept;
  size_type columns() const noexcept;

  void input(std::istream&);
  void output(std::ostream&) const;

  void resize(size_type, size_type);
  void fill(value_type);
  void clear() noexcept;

  void swap(Matrix&);

private:
  size_type rows_;
  size_type columns_;
  size_type size_;
  value_type* data_;
  bool is_initialized_;

  void reset();

  void checkBounds(size_type, size_type) const;
  void checkSizes(size_type, size_type) const;
  void checkIsInitialized() const;
  void checkIsEmpty() const;
};

#endif
