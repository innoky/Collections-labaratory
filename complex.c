#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

complex* new_complex(double real, double img)
{
    complex* c = (complex*)malloc(sizeof(complex));
    c->real = real;
    c->img = img;
    return c;
}

complex* complex_add(complex* a, complex* b)
{
    return new_complex(a->real + b->real, a->img + b->img);
}

complex* complex_mul(complex* a, complex* b)
{
    return new_complex(a->real * b->real - a->img * b->img, a->real * b->img + a->img * b->real);
}

void complex_print(complex* c)
{
    printf(" %g + %gi ", c->real, c->img);
}

void complex_free(complex* c)
{
    free(c);
}