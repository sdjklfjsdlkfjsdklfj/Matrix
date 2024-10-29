#include "matrix.h"
#include <cassert>
#include <iostream>
#include <sstream>

void testConstructors()
{
  Matrix m1(3, 3);
  assert(m1.rows() == 3);
  assert(m1.columns() == 3);

  Matrix m2(2, 2, 5);
  assert(m2.rows() == 2);
  assert(m2.columns() == 2);
  assert(m2.at(0, 0) == 5);
  assert(m2.at(1, 1) == 5);

  Matrix m3(m2);
  assert(m3.rows() == m2.rows());
  assert(m3.columns() == m2.columns());
  assert(m3.at(1, 1) == 5);

  Matrix m4(std::move(m2));
  assert(m4.rows() == 2 && m4.columns() == 2);
}
void testAssignmentOperators()
{
  Matrix m1(2, 2, 5);
  Matrix m2 = m1;
  assert(m2.rows() == m1.rows());
  assert(m2.columns() == m1.columns());
  assert(m2.at(1, 1) == 5);

  Matrix m3(3, 3, 10);
  m3 = std::move(m1);
  assert(m3.rows() == 2 && m3.columns() == 2);
  assert(m3.at(1, 1) == 5);
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
    assert(false && "Expected an out-of-bounds exception");
  } catch (const std::out_of_range&) {
  }
}

void testModifications()
{
  Matrix m(3, 3, 2);

  m.fill(7);
  assert(m.at(0, 0) == 7);
  assert(m.at(2, 2) == 7);

  m.clear();
  try {
    m.at(0, 0);
    assert(false && "Expected exception after clear()");
  } catch (const std::logic_error&) {
  }

  Matrix m1(2, 2, 1);
  Matrix m2(2, 2, 2);
  m1.swap(m2);
  assert(m1.at(0, 0) == 2);
  assert(m2.at(0, 0) == 1);
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
}

void testResize()
{
  Matrix m(2, 2, 3);
  m.resize(3, 3);

  assert(m.rows() == 3);
  assert(m.columns() == 3);

  assert(m.at(0, 0) == 3);
  assert(m.at(1, 1) == 3);

  assert(m.at(2, 2) == 0);
}

int main()
{
  testConstructors();
  testAssignmentOperators();
  testElementAccess();
  testModifications();
  testInputOutput();
  // testResize();
  std::cout << "All tests passed!\n";
  return 0;
}

