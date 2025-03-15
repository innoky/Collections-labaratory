#include "matrix.h"

#define TYPE_TO_FLAG_int 0
#define TYPE_TO_FLAG_float 1
#define TYPE_TO_FLAG_cmp 2

#define TYPE_TO_FLAG(type) TYPE_TO_FLAG_##type

#define MATRIX(name, rows, cols, type) matrix_t* name = matrix_create(rows, cols, TYPE_TO_FLAG(type))
#define MFILL(name, value, type) matrix_fill(name, value, TYPE_TO_FLAG(type))
#define MSET(name, row, col, value) matrix_set(name, row, col, value)
#define COMPLEX(name, real, img) MyComplex* name = new_complex(real, img);

#define MPRINT(matrix, BPrint) matrix_print(matrix, BPrint)