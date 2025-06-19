// MyComplex.h — по значению, без указателей
#ifndef MY_COMPLEX_H
#define MY_COMPLEX_H

typedef struct
{
    float real;
    float imag;
} MyComplex;

#define COMPLEX(name, re, im) MyComplex name = {re, im}

MyComplex complex_add(MyComplex a, MyComplex b);
MyComplex complex_sub(MyComplex a, MyComplex b);
MyComplex complex_mul(MyComplex a, MyComplex b);
int complex_equals(MyComplex a, MyComplex b);
void complex_print(MyComplex c);

#endif 
