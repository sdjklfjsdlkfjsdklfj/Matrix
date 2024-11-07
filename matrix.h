#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include <memory>

namespace math {

  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix&);
    Matrix(Matrix&&) noexcept;
    explicit Matrix(size_t, size_t);
    explicit Matrix(size_t, size_t, int value);
    ~Matrix() = default;

    Matrix& operator=(const Matrix&);
    Matrix& operator=(Matrix&& other) noexcept;

    int* operator[](size_t);
    const int* operator[](size_t) const;

    int& at(size_t, size_t);
    const int& at(size_t, size_t) const;

    size_t getRows() const noexcept;
    size_t getColumns() const noexcept;

    std::istream& input(std::istream&);
    std::ostream& output(std::ostream&) const;

    void resize(size_t, size_t);
    void fill(int);
    void clear() noexcept;

  private:
    size_t rows_;
    size_t columns_;
    std::unique_ptr<int[]> data_;
  };

}

#endif
