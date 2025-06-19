#ifndef MATRIX_H
#define MATRIX_H
#include "DataType.h"

typedef struct matrix
{
    int rows;
    int cols;
    void **data;
    const DataTypeOperations *ops;
} matrix_t;

matrix_t *matrix_create(int rows, int cols, const DataTypeOperations *ops);

matrix_t *matrix_sum(const matrix_t *a, const matrix_t *b);
matrix_t *matrix_mul(const matrix_t *a, const matrix_t *b);
matrix_t *matrix_transpose(const matrix_t *m);
matrix_t *add_linnear_comb(const matrix_t *m, int row, const void *coef);
void *matrix_get(const matrix_t *m, int row, int col);

void matrix_fill(matrix_t *m, const void *value);
void matrix_set(matrix_t *m, int row, int col, const void *value);
void matrix_print(const matrix_t *m, short int);
void matrix_destroy(matrix_t *m);

// Макросы для удобства
#define MATRIX(name, r, c, type_ops) \
    matrix_t *name = matrix_create((r), (c), &(type_ops))
#define MFILL(mat, val) matrix_fill((mat), (val))
#define MSET(mat, row, col, val) matrix_set((mat), (row), (col), (val))

#endif 

