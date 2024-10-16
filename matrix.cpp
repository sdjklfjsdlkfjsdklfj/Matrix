#include "matrix.h"

int** createMatrix(int**, size_t rows, size_t columns) {
    int** matrix = new int*[rows];
    size_t created = 0;
    try {
        for (; created < columns; ++created) {
            matrix[created] = new int[columns];
        }
    } catch (const std::bad_alloc& e) {
        deleteMatrix(matrix, created);
        throw;
    }
    return matrix;
}

void deleteMatrix(int** matrix, size_t rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
