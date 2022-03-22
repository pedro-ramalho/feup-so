#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

matrix* matrix_new(int rows, int cols) {
  matrix* m = (matrix*) malloc (sizeof(matrix));
  m->rows = rows;
  m->cols = cols;
  return m;
}

matrix* matrix_add(matrix* a, matrix* b) {
  if (a->rows != b->rows || a->cols != b->cols) return NULL;

  const int num_rows = a->rows;
  const int num_cols = b->cols;
  matrix* result = matrix_new(num_rows, num_cols);

  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++)
      (result->vals)[i][j] = (a->vals)[i][j];
}