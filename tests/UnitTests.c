#include "unity/unity.h"
#include "../src/DataType.h"
#include "../src/matrix.h"
#include "../src/MyComplex.h"

void setUp() {}
void tearDown() {}

void test_matrix_sum_complex()
{
    MATRIX(m1, 2, 2, cmp);
    MATRIX(m2, 2, 2, cmp);

    COMPLEX(c1, 3, 5);
    COMPLEX(c2, 5, 6);
    COMPLEX(c3, 2, 3);
    COMPLEX(c4, 1, 7);

    MSET(m1, 0, 0, &c1);
    MSET(m1, 0, 1, &c2);
    MSET(m2, 1, 0, &c3);
    MSET(m2, 1, 1, &c4);

    matrix_t *m3 = matrix_sum(m1, m2);

    MyComplex *element_a = (MyComplex *)matrix_get(m3, 1, 0);
    MyComplex *element_b = (MyComplex *)matrix_get(m3, 1, 1);

    MyComplex expected_a = {2, 3};
    MyComplex expected_b = {1, 7};

    TEST_ASSERT_TRUE(complex_equals(*element_a, expected_a));
    TEST_ASSERT_TRUE(complex_equals(*element_b, expected_b));

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}

void test_matrix_mul_complex()
{
    MATRIX(m1, 2, 2, cmp);
    MATRIX(m2, 2, 2, cmp);

    COMPLEX(c1, 1, 1);
    COMPLEX(c2, 2, 2);
    COMPLEX(c3, 3, 3);
    COMPLEX(c4, 4, 4);

    MSET(m1, 0, 0, &c1);
    MSET(m1, 0, 1, &c2);
    MSET(m1, 1, 0, &c3);
    MSET(m1, 1, 1, &c4);

    COMPLEX(c5, 5, -1);
    COMPLEX(c6, 6, -2);
    COMPLEX(c7, 7, -3);
    COMPLEX(c8, 8, -4);

    MSET(m2, 0, 0, &c5);
    MSET(m2, 0, 1, &c6);
    MSET(m2, 1, 0, &c7);
    MSET(m2, 1, 1, &c8);

    matrix_t *m3 = matrix_mul(m1, m2);

    MyComplex expected_00 = {26, 12};
    MyComplex expected_11 = {72, 28};

    MyComplex *elem_00 = (MyComplex *)matrix_get(m3, 0, 0);
    MyComplex *elem_11 = (MyComplex *)matrix_get(m3, 1, 1);

    TEST_ASSERT_TRUE(complex_equals(*elem_00, expected_00));
    TEST_ASSERT_TRUE(complex_equals(*elem_11, expected_11));

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}

void test_matrix_transpose_complex()
{
    MATRIX(m1, 2, 2, cmp);
    COMPLEX(c1, 1, 1);
    COMPLEX(c2, 2, 2);
    COMPLEX(c3, 3, 3);
    COMPLEX(c4, 4, 4);

    MSET(m1, 0, 0, &c1);
    MSET(m1, 0, 1, &c2);
    MSET(m1, 1, 0, &c3);
    MSET(m1, 1, 1, &c4);

    matrix_t *mT = matrix_transpose(m1);

    MyComplex *elem = (MyComplex *)matrix_get(mT, 0, 1);
    TEST_ASSERT_TRUE(complex_equals(*elem, c3));

    matrix_destroy(m1);
    matrix_destroy(mT);
}

void test_matrix_add_linear_comb_complex()
{
    MATRIX(m, 2, 2, cmp);
    COMPLEX(c1, 1, 1);
    COMPLEX(c2, 2, 2);
    COMPLEX(c3, 3, 3);
    COMPLEX(c4, 4, 4);

    MSET(m, 0, 0, &c1);
    MSET(m, 0, 1, &c2);
    MSET(m, 1, 0, &c3);
    MSET(m, 1, 1, &c4);

    COMPLEX(coef, 2, -1);
    matrix_t *res = add_linnear_comb(m, 0, &coef);

    MyComplex exp0 = {10, 4};
    MyComplex exp1 = {14, 6};
    MyComplex *res_val0 = (MyComplex *)matrix_get(res, 0, 0);
    MyComplex *res_val1 = (MyComplex *)matrix_get(res, 0, 1);

    TEST_ASSERT_TRUE(complex_equals(*res_val0, exp0));
    TEST_ASSERT_TRUE(complex_equals(*res_val1, exp1));

    matrix_destroy(m);
    matrix_destroy(res);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_matrix_sum_complex);
    RUN_TEST(test_matrix_mul_complex);
    RUN_TEST(test_matrix_transpose_complex);
    RUN_TEST(test_matrix_add_linear_comb_complex);
    return UNITY_END();
}
