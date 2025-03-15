#include <stdio.h>
#include <stdlib.h>
#include "MyComplex.h"

MyComplex* new_complex(float real, float img)
{
    MyComplex* c = (MyComplex*)malloc(sizeof(MyComplex));
    c->real = real;
    c->img = img;
    return c;
}

MyComplex* complex_add(MyComplex* a, MyComplex* b)
{
    return new_complex(a->real + b->real, a->img + b->img);
}

MyComplex* complex_mul(MyComplex* a, MyComplex* b)
{
    return new_complex(a->real * b->real - a->img * b->img, a->real * b->img + a->img * b->real);
}

int complex_equals(MyComplex *a, MyComplex *b)
{
    if (a->real == b->real && a->img == b->img)
    {
        return 1;
    }
    return 0;
}

void complex_print(MyComplex* c)
{
    printf(" %g + %gi ", c->real, c->img);
}

void complex_free(MyComplex* c)
{
    free(c);
}