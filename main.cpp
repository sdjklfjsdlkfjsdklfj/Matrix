#include <iostream>

#include "matrix.h"

int main() {
    size_t rows = 0;
    size_t columns = 0;

    std::cin >> rows >> columns;
    int** matrix = createMatrix(rows, columns);

    deleteMatrix(matrix, rows, columns);
}
