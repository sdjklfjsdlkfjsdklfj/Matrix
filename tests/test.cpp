#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include "matrix.h"

void testConstructors()
{
  Matrix m1;
  assert(m1.getRows() == 0);
  assert(m1.getColumns() == 0);

  Matrix m2(2, 3, 5);
  assert(m2.getRows() == 2);
  assert(m2.getColumns() == 3);
  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      assert(m2.at(i, j) == 5);
    }
  }

  Matrix m_large(1000, 1000, 1);
  assert(m_large.getRows() == 1000);
  assert(m_large.getColumns() == 1000);
  assert(m_large.at(999, 999) == 1);
}

void testAssignmentOperators()
{
  Matrix m1(2, 2, 5);
  Matrix m2 = m1;
  assert(m2.getRows() == m1.getRows());
  assert(m2.getColumns() == m1.getColumns());
  assert(m2.at(1, 1) == 5);

  Matrix m3(3, 3, 10);
  m3 = std::move(m1);
  assert(m3.getRows() == 2 && m3.getColumns() == 2);
  assert(m3.at(1, 1) == 5);

  Matrix m_empty;
  m_empty = m3;
  assert(m_empty.getRows() == 2);
  assert(m_empty.getColumns() == 2);
  assert(m_empty.at(1, 1) == 5);
}

void testElementAccess()
{
  Matrix m(3, 3, 0);
  m[1][1] = 10;
  assert(m.at(1, 1) == 10);

  const Matrix m_const = m;
  assert(m_const[1][1] == 10);

  try {
    m.at(3, 3);
    assert(false && "Expected out_of_range exception for bounds");
  } catch (const std::out_of_range&) {
  }

  try {
    m.at(-1, -1);
    assert(false && "Expected out_of_range exception for invalid negative index");
  } catch (const std::out_of_range&) {
  }
}

void testModifications()
{
  Matrix m(3, 3, 2);

  m.fill(7);
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      assert(m.at(i, j) == 7);
    }
  }

  m.clear();
  assert(m.getRows() == 0 && m.getColumns() == 0);
  try {
    m.at(0, 0);
    assert(false && "Expected exception after clear()");
  } catch (const std::logic_error&) {
  }
}

void testInputOutput()
{
  Matrix m(2, 2);
  std::istringstream is("1 2 3 4");
  m.input(is);
  assert(m.at(0, 0) == 1);
  assert(m.at(1, 1) == 4);

  std::ostringstream os;
  m.output(os);
  assert(os.str() == "1 2\n3 4\n");

  std::istringstream invalid_is("a b c d");
  invalid_is.exceptions(std::ios_base::failbit);
  try {
    m.input(invalid_is);
    assert(false && "Expected failure on non-numeric input");
  } catch (const std::ios_base::failure&) {
  }
}

void testResize()
{
  Matrix m(2, 2, 3);
  m.resize(3, 3);
  assert(m.getRows() == 3 && m.getColumns() == 3);
  assert(m.at(0, 0) == 3 && m.at(1, 1) == 3);

  assert(m.at(2, 2) == 0);

  m.resize(1, 1);
  assert(m.getRows() == 1 && m.getColumns() == 1);
  assert(m.at(0, 0) == 3);

  m.resize(0, 0);
  assert(m.getRows() == 0 && m.getColumns() == 0);
  try {
    m.at(0, 0);
    assert(false && "Expected exception when accessing elements after resize(0,0)");
  } catch (const std::logic_error&) {
  }
}

void testLargeMatrices()
{
  try {
    Matrix m(std::numeric_limits<size_t>::max(), 2);
    assert(false && "Expected exception for large matrix allocation");
  } catch (const std::bad_alloc&) {
  }

  try {
    Matrix m2(200, std::numeric_limits<size_t>::max());
    assert(false && "Expected exception for large matrix allocation");
  } catch (const std::bad_alloc&) {
  }
}

void testRandomOperations()
{
  Matrix m(10, 10);
  m.fill(1);

  for (size_t i = 0; i < 10; ++i) {
    for (size_t j = 0; j < 10; ++j) {
      m.at(i, j) = i * j;
    }
  }

  for (size_t i = 0; i < 10; ++i) {
    for (size_t j = 0; j < 10; ++j) {
      assert(m.at(i, j) == static_cast<int>(i * j));
    }
  }
}

int main()
{
  testConstructors();
  testAssignmentOperators();
  testElementAccess();
  testModifications();
  testInputOutput();
  testResize();
  testLargeMatrices();
  testRandomOperations();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}

