#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include "matrix.h"

using namespace math;

void testDefaultConstructor()
{
  Matrix m;
  assert(m.getRows() == 0);
  assert(m.getColumns() == 0);
}

void testParameterizedConstructor()
{
  Matrix m(3, 4, -1);
  assert(m.getRows() == 3);
  assert(m.getColumns() == 4);
  for (size_t i = 0; i < m.getRows(); ++i)
    for (size_t j = 0; j < m.getColumns(); ++j)
      assert(m[i][j] == -1);
}

void testCopyConstructorAndAssignment()
{
  Matrix m1(2, 3, 5);
  Matrix m2 = m1;
  assert(m2.getRows() == 2 && m2.getColumns() == 3);
  assert(m2[1][2] == 5);

  Matrix m3(1, 1);
  m3 = m2;
  assert(m3.getRows() == 2 && m3.getColumns() == 3);
  assert(m3[1][2] == 5);
}

void testMoveConstructorAndAssignment()
{
  Matrix m1(2, 3, 5);
  Matrix m2 = std::move(m1);
  assert(m2.getRows() == 2 && m2.getColumns() == 3);
  assert(m2[1][2] == 5);

  Matrix m3;
  m3 = std::move(m2);
  assert(m3.getRows() == 2 && m3.getColumns() == 3);
  assert(m3[1][2] == 5);
}

void testElementAccess()
{
  Matrix m(3, 3, 0);
  m[1][1] = 10;
  assert(m[1][1] == 10);

  const Matrix m_const = m;
  assert(m_const[1][1] == 10);
}

void testFill()
{
  Matrix m(4, 4, 1);
  m.fill(3);
  for (size_t i = 0; i < m.getRows(); ++i)
    for (size_t j = 0; j < m.getColumns(); ++j)
      assert(m[i][j] == 3);
}

void testClear()
{
  Matrix m(3, 3, 2);
  m.clear();
  assert(m.getRows() == 0);
  assert(m.getColumns() == 0);
}

void testResize()
{
  Matrix m(2, 2, 3);
  m.resize(3, 3);
  assert(m.getRows() == 3);
  assert(m.getColumns() == 3);
  assert(m[0][0] == 3 && m[2][2] == 0);

  m.resize(1, 1);
  assert(m.getRows() == 1 && m.getColumns() == 1);
  assert(m[0][0] == 3);

  m.resize(0, 0);
  assert(m.getRows() == 0 && m.getColumns() == 0);
}

void testInput()
{
  Matrix m(2, 2);
  std::istringstream is("1 2 3 4");
  is >> m;
  assert(m[0][0] == 1 && m[1][1] == 4);
}

void testOutput()
{
  Matrix m(2, 2);
  std::istringstream is("1 2 3 4");
  is >> m;
  std::ostringstream os;
  os << m;
  assert(os.str() == "1 2\n3 4");
}

void testSizesOverflow()
{
  try {
    Matrix m(std::numeric_limits<size_t>::max(), 2);
    assert(false);
  } catch (const std::bad_alloc&) {
  }

  try {
    Matrix m(200, std::numeric_limits<size_t>::max());
    assert(false);
  } catch (const std::bad_alloc&) {
  }
}

void testRandomData()
{
  Matrix m(5, 5);
  for (size_t i = 0; i < m.getRows(); ++i)
    for (size_t j = 0; j < m.getColumns(); ++j)
      m[i][j] = i * j;
  for (size_t i = 0; i < m.getRows(); ++i)
    for (size_t j = 0; j < m.getColumns(); ++j)
      assert(m[i][j] == static_cast<int>(i * j));

  m = Matrix(1000, 1000, 1);
  for (size_t i = 0; i < m.getRows(); ++i)
    for (size_t j = 0; j < m.getColumns(); ++j)
      m[i][j] += 1;
  assert(m[500][500] == 2);
}

int main()
{
  testDefaultConstructor();
  testParameterizedConstructor();
  testCopyConstructorAndAssignment();
  testMoveConstructorAndAssignment();
  testElementAccess();
  testFill();
  testClear();
  testResize();
  testInput();
  testOutput();
  testRandomData();

  std::cout << "All tests passed successfully.\n";
}

