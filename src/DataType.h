#pragma once

#include "types.h"

#define MATRIX(name, r, c, type) matrix_t *name = matrix_create(r, c, get##type##FieldInfo())
#define MFILL(matrix, val, type) matrix_fill(matrix, val, get##type##FieldInfo())
#define MSET(matrix, i, j, val) matrix_set(matrix, i, j, val)
#define MGET(matrix, i, j) matrix_get(matrix, i, j)

#define INT(name, val) Int *name = integer(val)
#define FLOAT(name, val) Float *name = float_(val)
#define DOUBLE(name, val) Double *name = double_(val)
#define COMPLEX(name, real, imag) MyComplex name = {real, imag}

#define getcmpFieldInfo getComplexFieldInfo
