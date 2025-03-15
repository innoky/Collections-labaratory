#include <stdio.h>
#include <stdlib.h>
#include "DataType.h"
#include "MyComplex.h"
#include "matrix.h"

matrix_t* matrix_create(int rows, int cols, short type) 
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
            element_size = sizeof(float);  break;
        case 2:
            element_size = sizeof(MyComplex);  break;
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
        else
        {
            for (int j = 0; j < cols; j++) 
            {
                switch (type) 
                {
                    case 0:
                        ((int**)m->data)[i][j] = 0; break;
                    case 1:
                        ((float**)m->data)[i][j] = 0.0; break;
                    case 2:
                        COMPLEX(z, 0.0, 0.0);
                        ((MyComplex**)m->data)[i][j] = *z; break;
                }
            }
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
                    printf(" %g ", ((float **)m->data)[i][j]);
                    break;
                case 2:
                    complex_print(&((MyComplex**)m->data)[i][j]);
                    break;
            }
            
        }
        if(BPrint == 1){printf("||");}
        printf("\n");
    }
    printf("////////////  MATRIX END  ////////////\n\n");
}

void matrix_fill(matrix_t *m, void* value, short type)
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
                    ((float**)m->data)[i][j] = *((float*)value);
                    break;
                case 2:
                    ((MyComplex**)m->data)[i][j] = *((MyComplex*)value);
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
        ((float **)m->data)[row][col] = *((float *)value);
        break;
    case 2:
        ((MyComplex **)m->data)[row][col] = *((MyComplex *)value);
        break;
    }
}

void* matrix_get(matrix_t *m, int row, int col)
{
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols)
    {
        printf("Error: out of bounds\n");
        exit(1);
    }

    switch (m->type)
    {
    case 0:
        return &((int **)m->data)[row][col];
    case 1:
        return &((float **)m->data)[row][col];
    case 2:
        return &((MyComplex **)m->data)[row][col];
    default:
        printf("Error: unknown type\n");
        return NULL;
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
                    ((float**)c->data)[i][j] = ((float**)a->data)[i][j] + ((float**)b->data)[i][j];
                    break;
                case 2:
                    MyComplex *sm = complex_add(&((MyComplex**)a->data)[i][j], &((MyComplex**)b->data)[i][j]);
                    ((MyComplex**)c->data)[i][j] = *sm;
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
                    ((float**)c->data)[i][j] = 0;
                    for (int k = 0; k < a->cols; k++) {
                        ((float**)c->data)[i][j] += ((float**)a->data)[i][k] * ((float**)b->data)[k][j];
                    }
                    break;
                case 2:
                    COMPLEX(sum, 0.0, 0.0);
                    ((MyComplex**)c->data)[i][j] = *sum;
                    for (int k = 0; k < a->cols; k++) {
                        MyComplex* mull = complex_mul(&((MyComplex**)a->data)[i][k], &((MyComplex**)b->data)[k][j]);
                        MyComplex* result = complex_add(&((MyComplex**)c->data)[i][j], mull);
                        ((MyComplex**)c->data)[i][j] = *result;
                        complex_free(mull);
                        complex_free(result);
                    }
                    break;
            }
        }
    }
    return c;
}

matrix_t* matrix_transpose(matrix_t *m) {
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
                    ((float**)t->data)[j][i] = ((float**)m->data)[i][j];
                    break;
                case 2:
                    ((MyComplex**)t->data)[j][i] = ((MyComplex**)m->data)[i][j];
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
                    ((float**)t->data)[i][j] = ((float**)m->data)[i][j];
                    break;
                case 2:
                    ((MyComplex**)t->data)[i][j] = ((MyComplex**)m->data)[i][j];
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
                        ((float**)t->data)[row][j] += ((float**)m->data)[i][j] * (*(float*)coef);
                        break;
                    case 2:
                        MyComplex* temp = complex_mul(&((MyComplex**)m->data)[i][j], (MyComplex*)coef);
                        MyComplex* result = complex_add(&((MyComplex**)t->data)[row][j], temp);
                        ((MyComplex**)t->data)[row][j] = *result;
                        complex_free(temp);
                        complex_free(result);
                        break;
                }
            }
        }
    }

    return t;
}
