#include <stdio.h>
#include <stdlib.h>
#include "DataType.h"
#include "complex.h"
#include "matrix.h"

matrix_t* matrix_create(int rows, int cols, int type) 
{  
    matrix_t *m = (matrix_t*)malloc(sizeof(matrix_t));
    if (m == NULL) return NULL; 
    m->rows = rows;
    m->cols = cols;
    m->type = type;
    size_t element_size;
    switch (type) 
    {
        case 0:
            element_size = sizeof(int);  break;
        case 1:
            element_size = sizeof(double);  break;
        case 2:
            element_size = sizeof(complex);  break;
        default:
            printf("Error: invalid type\n"); exit(0); 
    }
    m->data = (void**)malloc(rows * sizeof(void*));

    if (m->data == NULL) {
        free(m);
        return printf("Error: memory allocation failed\n"), NULL; 
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        m->data[i] = malloc(cols * element_size);
        if (m->data[i] == NULL) 
        {
            for (int j = 0; j < i; j++)free(m->data[j]);
            return free(m->data), free(m), NULL; 
        }
    }
    return m;
}

void matrix_destroy(matrix_t *m) {
    for (int i = 0; i < m->rows; i++) free(m->data[i]);
    free(m->data);
    free(m);
}

void matrix_print(matrix_t *m, short BPrint) {
    printf("////////////  MATRIX START  ////////////\n");
    for (int i = 0; i < m->rows; i++) {
        // Arg for beautiful print
        if(BPrint==1){printf("||");}
        for (int j = 0; j < m->cols; j++) {
            
            switch (m->type) {
                case 0:
                    printf(" %d ", ((int**)m->data)[i][j]);
                    break;
                case 1:
                    printf(" %g ", ((double **)m->data)[i][j]);
                    break;
                case 2:
                    complex_print(&((complex**)m->data)[i][j]);
                    break;
            }
            
        }
        if(BPrint == 1){printf("||");}
        printf("\n");
    }
    printf("////////////  MATRIX END  ////////////\n\n");
}

void matrix_fill(matrix_t *m, void* value, int type)
{
    if (!m || !value) {
        printf("Type error: null matrix or value\n");
        exit(1);
    }
    if (m->type != type) {
        fprintf(stderr, "Type error: incorrect value type for this matrix\n");
        exit(1);
    }
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            switch (m->type) {
                case 0:
                    ((int**)m->data)[i][j] = *((int*)value);
                    break;
                case 1:
                    ((double**)m->data)[i][j] = *((double*)value);
                    break;
                case 2:
                    ((complex**)m->data)[i][j] = *((complex*)value);
                    break;
            }
        }
    }
}

void matrix_set(matrix_t *m, int row, int col, void *value)
{
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols)
    {
        printf("Error: out of bounds\n");
        exit(1);
    }

    switch (m->type)
    {
    case 0:
        ((int **)m->data)[row][col] = *((int *)value);
        break;
    case 1:
        ((double **)m->data)[row][col] = *((double *)value);
        break;
    case 2:
        ((complex **)m->data)[row][col] = *((complex *)value);
        break;
    }
}

matrix_t* matrix_sum(matrix_t *a, matrix_t *b) {
    if (a->rows != b->rows || a->cols != b->cols || a->type != b->type) {
        printf("Error: incompatible matrices\n");
        exit(1);
    }

    matrix_t *c = matrix_create(a->rows, a->cols, a->type);
    if (c == NULL) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            switch (a->type) {
                case 0:
                    ((int**)c->data)[i][j] = ((int**)a->data)[i][j] + ((int**)b->data)[i][j];
                    break;
                case 1:
                    ((double**)c->data)[i][j] = ((double**)a->data)[i][j] + ((double**)b->data)[i][j];
                    break;
                case 2:
                    complex *sm = complex_add(&((complex**)a->data)[i][j], &((complex**)b->data)[i][j]);
                    ((complex**)c->data)[i][j] = *sm;
                    free(sm);
                    break;
            }
        }
    }
    return c;
}

matrix_t* matrix_mul(matrix_t *a, matrix_t *b) {
    if (a->cols != b->rows) {
        printf("Error: incompatible matrices\n");
        exit(1);
    }

    matrix_t *c = matrix_create(a->rows, b->cols, a->type);
    if (c == NULL) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            switch (a->type) {
                case 0:
                    ((int**)c->data)[i][j] = 0;
                    for (int k = 0; k < a->cols; k++) {
                        ((int**)c->data)[i][j] += ((int**)a->data)[i][k] * ((int**)b->data)[k][j];
                    }
                    break;
                case 1:
                    ((double**)c->data)[i][j] = 0;
                    for (int k = 0; k < a->cols; k++) {
                        ((double**)c->data)[i][j] += ((double**)a->data)[i][k] * ((double**)b->data)[k][j];
                    }
                    break;
                case 2:
                    Complex(sum, 0.0, 0.0);
                    ((complex**)c->data)[i][j] = *sum;
                    for (int k = 0; k < a->cols; k++) {
                        complex* mull = complex_mul(&((complex**)a->data)[i][k], &((complex**)b->data)[k][j]);
                        complex* result = complex_add(&((complex**)c->data)[i][j], mull);
                        ((complex**)c->data)[i][j] = *result;
                        complex_free(mull);
                        complex_free(result);
                    }
                    break;
            }
        }
    }
    return c;
}

matrix_t* transpose(matrix_t *m) {
    matrix_t *t = matrix_create(m->cols, m->rows, m->type);
    if (t == NULL) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            switch (m->type) {
                case 0:
                    ((int**)t->data)[j][i] = ((int**)m->data)[i][j];
                    break;
                case 1:
                    ((double**)t->data)[j][i] = ((double**)m->data)[i][j];
                    break;
                case 2:
                    ((complex**)t->data)[j][i] = ((complex**)m->data)[i][j];
                    break;
            }
        }
    }
    return t;
}

matrix_t* add_linnear_comb(matrix_t* m, int row, void* coef) 
{
    matrix_t* t = matrix_create(m->rows, m->cols, m->type);
    if (t == NULL) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            switch (m->type) {
                case 0:
                    ((int**)t->data)[i][j] = ((int**)m->data)[i][j];
                    break;
                case 1:
                    ((double**)t->data)[i][j] = ((double**)m->data)[i][j];
                    break;
                case 2:
                    ((complex**)t->data)[i][j] = ((complex**)m->data)[i][j];
                    break;
            }
        }
    }

    for (int i = 0; i < m->rows; i++) {
        if (i != row) {
            for (int j = 0; j < m->cols; j++) {
                switch (m->type) {
                    case 0:
                        ((int**)t->data)[row][j] += ((int**)m->data)[i][j] * (*(int*)coef);
                        break;
                    case 1:
                        ((double**)t->data)[row][j] += ((double**)m->data)[i][j] * (*(double*)coef);
                        break;
                    case 2:
                        complex* temp = complex_mul(&((complex**)m->data)[i][j], (complex*)coef);
                        complex* result = complex_add(&((complex**)t->data)[row][j], temp);
                        ((complex**)t->data)[row][j] = *result;
                        complex_free(temp);
                        complex_free(result);
                        break;
                }
            }
        }
    }

    return t;
}
