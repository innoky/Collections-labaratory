#include "matrix.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

matrix_t *matrix_create(int rows, int cols, FieldInfo *info)
{
    matrix_t *m = malloc(sizeof(matrix_t));
    if (!m)
        return NULL;

    m->rows = rows;
    m->cols = cols;
    m->info = info;

    m->data = malloc(sizeof(void *) * rows);
    for (int i = 0; i < rows; i++)
    {
        m->data[i] = calloc(cols, info->element_size);
    }

    return m;
}

void matrix_destroy(matrix_t *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void matrix_print(matrix_t *m, short BPrint)
{
    printf("Matrix %dx%d:\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        if (BPrint)
            printf("|");
        for (int j = 0; j < m->cols; j++)
        {
            void *element = (char *)m->data[i] + j * m->info->element_size;
            m->info->toString(element);
        }
        if (BPrint)
            printf("|");
        printf("\n");
    }
}

void matrix_set(matrix_t *m, int row, int col, void *value)
{
    void *target = (char *)m->data[row] + col * m->info->element_size;
    memcpy(target, value, m->info->element_size);
}

void *matrix_get(matrix_t *m, int row, int col)
{
    return (char *)m->data[row] + col * m->info->element_size;
}
void matrix_fill(matrix_t *m, void *value, FieldInfo *info)
{
    if (m->info != info)
    {
        fprintf(stderr, "Type mismatch in matrix_fill\n");
        exit(1);
    }
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            matrix_set(m, i, j, value);
}

matrix_t *matrix_sum(matrix_t *a, matrix_t *b)
{

    matrix_t *res = matrix_create(a->rows, a->cols, a->info); 
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            void *x = matrix_get(a, i, j);
            void *y = matrix_get(b, i, j);
            void *r = sum(a->info, x, y);
            matrix_set(res, i, j, r);
            free(r);
        }
    }
    return res;
}

matrix_t *matrix_mul(matrix_t *a, matrix_t *b)
{


    matrix_t *res = matrix_create(a->rows, b->cols, a->info);

    for (int i = 0; i < res->rows; i++)
    {
        for (int j = 0; j < res->cols; j++)
        {
            void *acc = Zero(a->info);
            for (int k = 0; k < a->cols; k++)
            {
                void *x = matrix_get(a, i, k);
                void *y = matrix_get(b, k, j);
                void *prod = product(a->info, x, y);
                void *new_acc = sum(a->info, acc, prod);
                free(acc);
                free(prod);
                acc = new_acc;
            }
            matrix_set(res, i, j, acc);
            free(acc);
        }
    }

    return res;
}

matrix_t *matrix_transpose(matrix_t *m)
{
    matrix_t *t = matrix_create(m->cols, m->rows, m->info); 
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            void *val = matrix_get(m, i, j);
            matrix_set(t, j, i, val);
        }
    }
    return t;
}

matrix_t *add_linnear_comb(matrix_t *m, int row, void *coef)
{
    matrix_t *res = matrix_create(m->rows, m->cols, m->info);

    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            void *val = matrix_get(m, i, j);
            matrix_set(res, i, j, val);
        }
    }

    for (int i = 0; i < m->rows; i++)
    {
        if (i == row)
            continue;
        for (int j = 0; j < m->cols; j++)
        {
            void *src = matrix_get(m, i, j);
            void *scaled = product(m->info, src, coef);
            void *dst = matrix_get(res, row, j);
            void *updated = sum(m->info, dst, scaled);
            matrix_set(res, row, j, updated);
            free(scaled);
            free(updated);
        }
    }
    return res;
}
