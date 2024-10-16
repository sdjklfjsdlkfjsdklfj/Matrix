#include "matrix.h"

int main() {
  size_t rows = 0;
  size_t columns = 0;

  if (!(std::cin >> rows >> columns)) {
    return 1;
  }
  int** matrix = nullptr;
  try {
    matrix = createMatrix(rows, columns);
  } catch (std::bad_alloc& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  };

  inputMatrix(std::cin, matrix, rows, columns);
  if (!std::cin.good()) {
    deleteMatrix(matrix, rows);
    return 1;
  }
  outputMatrix(std::cout, matrix, rows, columns);

  deleteMatrix(matrix, rows);
}
