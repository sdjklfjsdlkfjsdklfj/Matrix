#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
public:
  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;
  explicit Matrix(size_t, size_t, int value = int());
  ~Matrix() noexcept;

  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&& other) noexcept;

  int* operator[](size_t);
  const int* operator[](size_t) const;

  int& at(size_t, size_t);
  const int& at(size_t, size_t) const;

  size_t getRows() const noexcept;
  size_t getColumns() const noexcept;

  void input(std::istream&);
  void output(std::ostream&) const;

  void resize(size_t, size_t);
  void fill(int);
  void clear() noexcept;

private:
  size_t rows_;
  size_t columns_;
  size_t size_;
  int* data_;

  void reset();
  void swap(Matrix&);

  void checkBounds(size_t, size_t) const;
  void checkSizes(size_t, size_t) const;
};

#endif
