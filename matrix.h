#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

int** createMatrix(const size_t, const size_t);
void deleteMatrix(int**, const size_t);

int** inputMatrix(std::istream&, const size_t, const size_t);
void outputMatrix(std::ostream&, const int* const*, const size_t, const size_t);

#endif
