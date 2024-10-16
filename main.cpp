#include <iostream>

int** createMatrix(size_t, size_t);
void deleteMatrix(int**, size_t, size_t);

int main() {
    size_t rows = 0;
    size_t columns = 0;

    std::cin >> rows >> columns;
    int** matrix = createMatrix(rows, columns);

    deleteMatrix(matrix, rows, columns);
}
