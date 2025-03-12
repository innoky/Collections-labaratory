#include "matrix.h"

#define TYPE_TO_FLAG_int 0
#define TYPE_TO_FLAG_double 1
#define TYPE_TO_FLAG_complex 2

#define TYPE_TO_FLAG(type) TYPE_TO_FLAG_##type

#define MATRIX(name, rows, cols, type) matrix_t* name = matrix_create(rows, cols, TYPE_TO_FLAG(type))
#define MATRIX_FILL(name, value, type) matrix_fill(name, value, TYPE_TO_FLAG(type))
#define Complex(name, real, img) complex* name = new_complex(real, img);