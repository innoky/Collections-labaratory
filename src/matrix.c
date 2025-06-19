#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void print_element(const DataTypeOperations *ops, const void *element) {
    if (ops == &int_ops) {
        printf("%d ", *(const int *)element);
    } else if (ops == &double_ops) {
        printf("%g ", *(const double *)element);
    } else if (ops == &complex_ops) {
        extern void complex_print(MyComplex c);
        complex_print(*(const MyComplex *)element);
        printf(" ");
    } else {
        printf("? ");
    }
}

matrix_t *matrix_create(int rows, int cols, const DataTypeOperations *ops)
{
    matrix_t *m = malloc(sizeof(matrix_t));
    if (!m)
        return NULL;

    m->rows = rows;
    m->cols = cols;
    m->ops = ops;

    m->data = malloc(sizeof(void *) * rows);
    for (int i = 0; i < rows; i++) {
        m->data[i] = calloc(cols, ops->size);
    }

    return m;
}

void matrix_destroy(matrix_t *m)
{
    for (int i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void matrix_print(const matrix_t *m, short BPrint)
{
    printf("Matrix %dx%d:\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        if (BPrint)
            printf("|");
        for (int j = 0; j < m->cols; j++) {
            void *element = (char *)m->data[i] + j * m->ops->size;
            print_element(m->ops, element);
        }
        if (BPrint)
            printf("|");
        printf("\n");
    }
}

void matrix_set(matrix_t *m, int row, int col, const void *value)
{
    void *target = (char *)m->data[row] + col * m->ops->size;
    memcpy(target, value, m->ops->size);
}

void *matrix_get(const matrix_t *m, int row, int col)
{
    return (char *)m->data[row] + col * m->ops->size;
}

void matrix_fill(matrix_t *m, const void *value)
{
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            matrix_set(m, i, j, value);
}

matrix_t *matrix_sum(const matrix_t *a, const matrix_t *b)
{
    if (a->rows != b->rows || a->cols != b->cols || a->ops != b->ops) {
        fprintf(stderr, "Matrix sum: dimension/type mismatch\n");
        return NULL;
    }
    matrix_t *res = matrix_create(a->rows, a->cols, a->ops);
    void *tmp = malloc(a->ops->size);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            void *x = matrix_get(a, i, j);
            void *y = matrix_get(b, i, j);
            a->ops->sum(x, y, tmp);
            matrix_set(res, i, j, tmp);
        }
    }
    free(tmp);
    return res;
}

matrix_t *matrix_mul(const matrix_t *a, const matrix_t *b)
{
    if (a->cols != b->rows || a->ops != b->ops) {
        fprintf(stderr, "Matrix mul: dimension/type mismatch\n");
        return NULL;
    }
    matrix_t *res = matrix_create(a->rows, b->cols, a->ops);
    void *acc = malloc(a->ops->size);
    void *prod = malloc(a->ops->size);
    for (int i = 0; i < res->rows; i++) {
        for (int j = 0; j < res->cols; j++) {
            memset(acc, 0, a->ops->size); // zero accumulator
            for (int k = 0; k < a->cols; k++) {
                void *x = matrix_get(a, i, k);
                void *y = matrix_get(b, k, j);
                a->ops->multiply(x, y, prod);
                a->ops->sum(acc, prod, acc);
            }
            matrix_set(res, i, j, acc);
        }
    }
    free(acc);
    free(prod);
    return res;
}

matrix_t *matrix_transpose(const matrix_t *m)
{
    matrix_t *t = matrix_create(m->cols, m->rows, m->ops);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            void *val = matrix_get(m, i, j);
            matrix_set(t, j, i, val);
        }
    }
    return t;
}

matrix_t *add_linnear_comb(const matrix_t *m, int row, const void *coef)
{
    matrix_t *res = matrix_create(m->rows, m->cols, m->ops);
    void *tmp = malloc(m->ops->size);
    void *scaled = malloc(m->ops->size);
    // Копируем исходную матрицу
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            void *val = matrix_get(m, i, j);
            matrix_set(res, i, j, val);
        }
    }
    // Добавляем линейную комбинацию
    for (int i = 0; i < m->rows; i++) {
        if (i == row)
            continue;
        for (int j = 0; j < m->cols; j++) {
            void *src = matrix_get(m, i, j);
            m->ops->multiply(src, coef, scaled);
            void *dst = matrix_get(res, row, j);
            m->ops->sum(dst, scaled, tmp);
            matrix_set(res, row, j, tmp);
        }
    }
    free(tmp);
    free(scaled);
    return res;
}
