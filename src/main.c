#include <stdio.h>
#include <stdlib.h>

#include "DataType.h"
#include "matrix.h"
#include "MyComplex.h"

int main() {
    // Matrix creation
    MATRIX(m1, 3, 4, cmp);
    MATRIX(m2, 3, 4, cmp);
    MATRIX(m3, 4, 3, cmp);

    // Matrix filling / setting (with COMPLEX) and printing
    COMPLEX(c1, 3.3, 4);
    COMPLEX(c_f, 45.3, 2.4);
    MFILL(m1, &c1, cmp);
    MSET(m1, 1, 3, &c_f);
    printf("Filled matrix:\n");
    matrix_print(m1, 0);

    // Matrix summation and printing
    COMPLEX(c2, 3, 4);
    MFILL(m2, &c2, cmp);
    matrix_t* sum_matrix = matrix_sum(m1, m2);
    printf("Summed matrices:\n");
    matrix_print(sum_matrix, 0);

    // Matrix multiply and printing
    COMPLEX(c3, 5, 2);
    MFILL(m3, &c3, cmp);
    matrix_t* mul_matrix = matrix_mul(sum_matrix, m3);
    printf("Multiplied matrices:\n");
    matrix_print(mul_matrix, 0);

    // Matrix transpose and printing
    matrix_t* trans_matrix = matrix_transpose(mul_matrix);
    printf("Transposed matrix:\n");
    matrix_print(trans_matrix, 1);

    // Linear combination adding
    COMPLEX(coef, 5, 12);
    matrix_t* lin_added_matrix = add_linnear_comb(trans_matrix, 0, &coef);
    matrix_print(lin_added_matrix, 0);

    // Cleanup
    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
    matrix_destroy(sum_matrix);
    matrix_destroy(mul_matrix);
    matrix_destroy(trans_matrix);
    matrix_destroy(lin_added_matrix);

    return 0;
}