#include "unity/unity.h"
#include "../src/DataType.h"
#include "../src/matrix.h"
#include "../src/MyComplex.h"

void setUp() {}    
void tearDown() {}

/*************** Тесты для сложения матриц ***************/
void test_matrix_sum_int()
{
    MATRIX(m1, 2, 2, int);
    MATRIX(m2, 2, 2, int);
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    MSET(m1, 0, 0, &a);
    MSET(m1, 0, 1, &b);
    MSET(m2, 1, 0, &c);
    MSET(m2, 1, 1, &d);
    matrix_t *m3 = matrix_sum(m1, m2);

    int element_a = *((int *)matrix_get(m3, 1, 1));
    int element_b = *((int *)matrix_get(m3, 0, 1));

    TEST_ASSERT_EQUAL_INT(4, element_a);
    TEST_ASSERT_EQUAL_INT(2, element_b);

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}

void test_matrix_sum_float()
{
    MATRIX(m1, 2, 2, float);
    MATRIX(m2, 2, 2, float);
    float a = 1.1;
    float b = 2.2;
    float c = 3.3;
    float d = 4.4;

    MSET(m1, 0, 0, &a);
    MSET(m1, 0, 1, &b);
    MSET(m2, 1, 0, &c);
    MSET(m2, 1, 1, &d);
    matrix_t *m3 = matrix_sum(m1, m2);

    float element_a = *((float *)matrix_get(m3, 1, 1));
    float element_b = *((float *)matrix_get(m3, 0, 1));

    TEST_ASSERT_EQUAL_FLOAT(4.4, element_a);
    TEST_ASSERT_EQUAL_FLOAT(2.2, element_b); 

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}

void test_matrix_sum_complex()
{
    MATRIX(m1, 2, 2, cmp);
    MATRIX(m2, 2, 2, cmp);

    COMPLEX(c1, 3, 5);
    COMPLEX(c2, 5, 6);
    COMPLEX(c3, 2, 3);
    COMPLEX(c4, 1, 7);

    MSET(m1, 0, 0, c1);
    MSET(m1, 0, 1, c2);
    MSET(m2, 1, 0, c3);
    MSET(m2, 1, 1, c4);

    matrix_t *m3 = matrix_sum(m1, m2);

    COMPLEX(t1, 2,3);
    COMPLEX(t2, 1,7);
    MyComplex* element_a = ((MyComplex *)matrix_get(m3, 1, 0));
    MyComplex* element_b = ((MyComplex *)matrix_get(m3, 1, 1));

    TEST_ASSERT_TRUE(complex_equals(element_a, t1));
    TEST_ASSERT_TRUE(complex_equals(element_b, t2));

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}

/*************** Тесты для умножения матриц ***************/

void test_matrix_mul_int()
{
    MATRIX(m1, 2, 2, int);
    MATRIX(m2, 2, 2, int);
    /*
         A = [ [1, 2],
               [3, 4] ]
         B = [ [5, 6],
               [7, 8] ]
       Тогда A * B = [ [1*5 + 2*7, 1*6 + 2*8] = [19, 22],
                       [3*5 + 4*7, 3*6 + 4*8] = [43, 50] ]
    */
    int a = 1, b = 2, c = 3, d = 4;
    int e = 5, f = 6, g = 7, h = 8;

    MSET(m1, 0, 0, &a);
    MSET(m1, 0, 1, &b);
    MSET(m1, 1, 0, &c);
    MSET(m1, 1, 1, &d);

    MSET(m2, 0, 0, &e);
    MSET(m2, 0, 1, &f);
    MSET(m2, 1, 0, &g);
    MSET(m2, 1, 1, &h);

    matrix_t *m3 = matrix_mul(m1, m2);

    int elem_00 = *((int *)matrix_get(m3, 0, 0));
    int elem_11 = *((int *)matrix_get(m3, 1, 1));

    TEST_ASSERT_EQUAL_INT(19, elem_00);
    TEST_ASSERT_EQUAL_INT(50, elem_11);

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}

void test_matrix_mul_float()
{
    MATRIX(m1, 2, 2, float);
    MATRIX(m2, 2, 2, float);
    /*
         A = [ [1.1, 2.2],
               [3.3, 4.4] ]
         B = [ [5.5, 6.6],
               [7.7, 8.8] ]

         C[0,0] = 1.1*5.5 + 2.2*7.7 ≈ 6.05 + 16.94 = 22.99
         C[1,1] = 3.3*6.6 + 4.4*8.8 ≈ 21.78 + 38.72 = 60.50
    */
    float a = 1.1f, b = 2.2f, c = 3.3f, d = 4.4f;
    float e = 5.5f, f = 6.6f, g = 7.7f, h = 8.8f;

    MSET(m1, 0, 0, &a);
    MSET(m1, 0, 1, &b);
    MSET(m1, 1, 0, &c);
    MSET(m1, 1, 1, &d);

    MSET(m2, 0, 0, &e);
    MSET(m2, 0, 1, &f);
    MSET(m2, 1, 0, &g);
    MSET(m2, 1, 1, &h);

    matrix_t *m3 = matrix_mul(m1, m2);

    float elem_00 = *((float *)matrix_get(m3, 0, 0));
    float elem_11 = *((float *)matrix_get(m3, 1, 1));

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 22.99f, elem_00);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 60.50f, elem_11);

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}

void test_matrix_mul_complex()
{
    MATRIX(m1, 2, 2, cmp);
    MATRIX(m2, 2, 2, cmp);
    /* 
         m1 = [ [c1, c2],
                [c3, c4] ]
         где:
         c1 = (1,1), c2 = (2,2), c3 = (3,3), c4 = (4,4)
         m2 = [ [c5, c6],
                [c7, c8] ]
         где:
         c5 = (5,-1), c6 = (6,-2), c7 = (7,-3), c8 = (8,-4)
         Элемент [0,0]:
           = c1*c5 + c2*c7
           = (1,1)*(5,-1) + (2,2)*(7,-3)
           = (6,4) + (20,8) = (26,12)
         Элемент [1,1]:
           = c3*c6 + c4*c8
           = (3,3)*(6,-2) + (4,4)*(8,-4)
           = (24,12) + (48,16) = (72,28)
    */
    COMPLEX(c1, 1, 1)
    COMPLEX(c2, 2, 2)
    COMPLEX(c3, 3, 3)
    COMPLEX(c4, 4, 4)
    MSET(m1, 0, 0, c1);
    MSET(m1, 0, 1, c2);
    MSET(m1, 1, 0, c3);
    MSET(m1, 1, 1, c4);

    COMPLEX(c5, 5, -1)
    COMPLEX(c6, 6, -2)
    COMPLEX(c7, 7, -3)
    COMPLEX(c8, 8, -4)
    MSET(m2, 0, 0, c5);
    MSET(m2, 0, 1, c6);
    MSET(m2, 1, 0, c7);
    MSET(m2, 1, 1, c8);

    matrix_t *m3 = matrix_mul(m1, m2);

    /* Проверим два элемента */
    COMPLEX(expected_00, 26, 12);
    COMPLEX(expected_11, 72, 28);

    MyComplex *elem_00 = (MyComplex *)matrix_get(m3, 0, 0);
    MyComplex *elem_11 = (MyComplex *)matrix_get(m3, 1, 1);

    TEST_ASSERT_TRUE(complex_equals(elem_00, expected_00));
    TEST_ASSERT_TRUE(complex_equals(elem_11, expected_11));

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}

/*************** Тесты для транспонирования матриц ***************/

void test_matrix_transpose_int()
{
    MATRIX(m1, 2, 2, int);
    int a = 1, b = 2, c = 3, d = 4;

    MSET(m1, 0, 0, &a);
    MSET(m1, 0, 1, &b);
    MSET(m1, 1, 0, &c);
    MSET(m1, 1, 1, &d);

    matrix_t *mT = matrix_transpose(m1);

    int elem = *((int *)matrix_get(mT, 0, 1)); 
    TEST_ASSERT_EQUAL_INT(3, elem);

    matrix_destroy(m1);
    matrix_destroy(mT);
}

void test_matrix_transpose_float()
{
    MATRIX(m1, 2, 2, float);
    float a = 1.1f, b = 2.2f, c = 3.3f, d = 4.4f;

    MSET(m1, 0, 0, &a);
    MSET(m1, 0, 1, &b);
    MSET(m1, 1, 0, &c);
    MSET(m1, 1, 1, &d);

    matrix_t *mT = matrix_transpose(m1);

    float elem = *((float *)matrix_get(mT, 0, 1)); // ожидается 3.3
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 3.3f, elem);

    matrix_destroy(m1);
    matrix_destroy(mT);
}

void test_matrix_transpose_complex()
{
    MATRIX(m1, 2, 2, cmp);
    COMPLEX(c1, 1, 1)
    COMPLEX(c2, 2, 2)
    COMPLEX(c3, 3, 3)
    COMPLEX(c4, 4, 4)
    MSET(m1, 0, 0, c1);
    MSET(m1, 0, 1, c2);
    MSET(m1, 1, 0, c3);
    MSET(m1, 1, 1, c4);

    matrix_t *mT = matrix_transpose(m1);

    MyComplex *elem = (MyComplex *)matrix_get(mT, 0, 1);
    TEST_ASSERT_TRUE(complex_equals(elem, c3));

    matrix_destroy(m1);
    matrix_destroy(mT);
}

/*************** Тесты для линейной комбинации ***************/

void test_matrix_add_linear_comb_int()
{
    MATRIX(m, 2, 2, int);
    int a = 1, b = 2, c = 3, d = 4;
    MSET(m, 0, 0, &a);
    MSET(m, 0, 1, &b);
    MSET(m, 1, 0, &c);
    MSET(m, 1, 1, &d);

    int coef = 2;
    matrix_t *res = add_linnear_comb(m, 0, &coef);

    int res_val0 = *((int *)matrix_get(res, 0, 0));
    int res_val1 = *((int *)matrix_get(res, 0, 1));

    TEST_ASSERT_EQUAL_INT(7, res_val0);
    TEST_ASSERT_EQUAL_INT(10, res_val1);

    matrix_destroy(m);
    matrix_destroy(res);
}

void test_matrix_add_linear_comb_float()
{
    MATRIX(m, 2, 2, float);
    float a = 1.1f, b = 2.2f, c = 3.3f, d = 4.4f;
    MSET(m, 0, 0, &a);
    MSET(m, 0, 1, &b);
    MSET(m, 1, 0, &c);
    MSET(m, 1, 1, &d);

    float coef = 1.5f;
    matrix_t *res = add_linnear_comb(m, 1, &coef);

    float res_val0 = *((float *)matrix_get(res, 1, 0));
    float res_val1 = *((float *)matrix_get(res, 1, 1));

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 4.95f, res_val0);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 7.7f, res_val1);

    matrix_destroy(m);
    matrix_destroy(res);
}

void test_matrix_add_linear_comb_complex()
{
    MATRIX(m, 2, 2, cmp);
    COMPLEX(c1, 1, 1);
    COMPLEX(c2, 2, 2);
    COMPLEX(c3, 3, 3);
    COMPLEX(c4, 4, 4);
    MSET(m, 0, 0, c1);
    MSET(m, 0, 1, c2);
    MSET(m, 1, 0, c3);
    MSET(m, 1, 1, c4);

    COMPLEX(coef, 2, -1);
    matrix_t *res = add_linnear_comb(m, 0, coef);

    COMPLEX(exp0, 10, 4);
    COMPLEX(exp1, 14, 6);
    MyComplex *res_val0 = (MyComplex *)matrix_get(res, 0, 0);
    MyComplex *res_val1 = (MyComplex *)matrix_get(res, 0, 1);

    TEST_ASSERT_TRUE(complex_equals(res_val0, exp0));
    TEST_ASSERT_TRUE(complex_equals(res_val1, exp1));

    matrix_destroy(m);
    matrix_destroy(res);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_matrix_sum_int);
    RUN_TEST(test_matrix_sum_float);
    RUN_TEST(test_matrix_sum_complex);
    RUN_TEST(test_matrix_mul_int);
    RUN_TEST(test_matrix_mul_float);
    RUN_TEST(test_matrix_mul_complex);
    RUN_TEST(test_matrix_transpose_int);
    RUN_TEST(test_matrix_transpose_float);
    RUN_TEST(test_matrix_transpose_complex);
    RUN_TEST(test_matrix_add_linear_comb_int);
    RUN_TEST(test_matrix_add_linear_comb_float);
    RUN_TEST(test_matrix_add_linear_comb_complex);
    return UNITY_END();
}