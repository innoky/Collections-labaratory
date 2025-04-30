#include "MyComplex.h"
#include <math.h>
#include <stdio.h>

MyComplex complex_add(MyComplex a, MyComplex b)
{
    MyComplex r = {a.real + b.real, a.imag + b.imag};
    return r;
}

MyComplex complex_sub(MyComplex a, MyComplex b)
{
    MyComplex r = {a.real - b.real, a.imag - b.imag};
    return r;
}

MyComplex complex_mul(MyComplex a, MyComplex b)
{
    MyComplex r = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real};
    return r;
}



int complex_equals(MyComplex a, MyComplex b)
{
    return fabs(a.real - b.real) < 1e-3f && fabs(a.imag - b.imag) < 1e-3f;
}

void complex_print(MyComplex c)
{
    printf("%g + %gi", c.real, c.imag);
}
