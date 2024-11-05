#include <cassert>
#include <iostream>
#include <sstream>
#include "matrix.h"

void testConstructors()
{
  Matrix m1(3, 3);
  assert(m1.getRows() == 3);
  assert(m1.getColumns() == 3);

  Matrix m2(2, 2, 5);
  assert(m2.getRows() == 2);
  assert(m2.getColumns() == 2);
  assert(m2.at(0, 0) == 5);
  assert(m2.at(1, 1) == 5);

  Matrix m3(m2);
  assert(m3.getRows() == m2.getRows());
  assert(m3.getColumns() == m2.getColumns());
  assert(m3.at(1, 1) == 5);

  Matrix m4(std::move(m2));
  assert(m4.getRows() == 2 && m4.getColumns() == 2);
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

  assert(m.getRows() == 3);
  assert(m.getColumns() == 3);

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
  testResize();
  std::cout << "All tests passed!\n";
  return 0;
}

