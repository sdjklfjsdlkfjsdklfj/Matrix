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

  size_type getRows() const noexcept;
  size_type getColumns() const noexcept;

  value_type getMinimum() const;
  value_type getMaximum() const;
  value_type getSum() const;
  value_type getAverage() const;

  void input(std::istream&);
  void output(std::ostream&) const;

  void resize(size_type, size_type);
  void fill(value_type);
  void clear() noexcept;

private:
  size_type _rows;
  size_type _columns;
  value_type* _data;
};

#endif
