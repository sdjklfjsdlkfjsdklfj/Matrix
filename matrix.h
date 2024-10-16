#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

int** createMatrix(const size_t, const size_t);
void deleteMatrix(int* const*, const size_t);

void inputMatrix(std::istream&, int* const*, const size_t, const size_t);
void outputMatrix(std::ostream&, const int* const*, const size_t, const size_t);

#endif
