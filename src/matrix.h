#ifndef MATRIX_H
#define MATRIX_H
typedef struct matrix
{
    int rows;
    int cols;
    void** data;
    short type; 
} matrix_t;

matrix_t* matrix_create(int rows, int cols, short type);

matrix_t* matrix_sum(matrix_t *a, matrix_t *b);
matrix_t* matrix_mul(matrix_t *a, matrix_t *b);
matrix_t* matrix_transpose(matrix_t *m);
matrix_t* add_linnear_comb(matrix_t* m, int row, void* coef);
void* matrix_get(matrix_t *m, int row, int col);

void matrix_fill(matrix_t *m, void* value, short type);
void matrix_set(matrix_t *m, int row, int col, void* value);
void matrix_print(matrix_t *m, short int);
void matrix_destroy(matrix_t *m);

#endif 

