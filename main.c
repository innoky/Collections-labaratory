#include <stdio.h>
#include <stdlib.h>

#include "DataType.h"
#include "matrix.h"
#include "complex.h"


int main() {
    // Matrix creation
    MATRIX(m1, 3, 4, complex);
    MATRIX(m2, 3, 4, complex);
    MATRIX(m3, 4, 3, complex);

    // Matrix filling / setting (with Complex) and printing
    Complex(c1,3.3,4);
    Complex(c_f, 45.3, 2.4);
    matrix_fill(m1, c1, 2);
    matrix_set(m1,1,3,c_f);
    printf("Filled matrix:\n");
    matrix_print(m1, 0);

    // Matrix summation and printing
    Complex(c2, 3, 4);
    matrix_fill(m2, c2, 2);
    matrix_t* sum_matrix = matrix_sum(m1, m2);
    printf("Summed matrices:\n");
    matrix_print(sum_matrix, 0);

    //Matrix muliply and printing
    Complex(c3, 5, 2);
    matrix_fill(m3, c3, 2);
    matrix_t* mul_matrix = matrix_mul(sum_matrix, m3);
    printf("Multiplied matrices:\n");
    matrix_print(mul_matrix, 0);

    //Matrix transpose and printing
    matrix_t* trans_matrix = transpose(mul_matrix);
    printf("Transposed matrix:\n");
    matrix_print(trans_matrix, 1);

    //Linear combination adding
    Complex(coef, 5, 12);
    matrix_t* lin_added_matrix = add_linnear_comb(trans_matrix, 0, coef);
    matrix_print(lin_added_matrix, 0);

    return 0;
}