#include <iostream>
#include "matrix.h"

int main()
{
  size_t rows = 0;
  size_t columns = 0;

  if (!(std::cin >> rows >> columns)) {
    std::cerr << "Invalid input\n";
    return 1;
  }
  try {
    math::Matrix matrix(rows, columns);
    matrix.input(std::cin);
    if (!std::cin.good()) {
      std::cerr << "Invalid input\n";
      return 1;
    }
    matrix.output(std::cout);
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  };
}
