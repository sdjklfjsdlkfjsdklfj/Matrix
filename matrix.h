#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
public:
  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;
  explicit Matrix(size_t, size_t);
  explicit Matrix(size_t, size_t, int);
  ~Matrix() noexcept;

  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&& other) noexcept;

  int* operator[](size_t);
  const int* operator[](size_t) const;

  const int& at(size_t, size_t) const;
  int& at(size_t, size_t);

  size_t rows() const noexcept;
  size_t columns() const noexcept;

  void input(std::istream&);
  void output(std::ostream&) const;

  void resize(size_t, size_t);
  void fill(int);
  void clear() noexcept;

  void swap(Matrix&);

private:
  size_t rows_;
  size_t columns_;
  size_t size_;
  int* data_;
  bool is_initialized_;

  void reset();

  void checkBounds(size_t, size_t) const;
  void checkSizes(size_t, size_t) const;
  void checkIsInitialized() const;
  void checkIsEmpty() const;
};

#endif
