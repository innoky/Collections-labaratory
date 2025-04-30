#include "types.h"
#include "MyComplex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FieldInfo *INT_FIELD_INFO = NULL;
FieldInfo *DOUBLE_FIELD_INFO = NULL;
FieldInfo *FLOAT_FIELD_INFO = NULL;
FieldInfo *COMPLEX_FIELD_INFO = NULL;

void int_to_string(void *element)
{
    printf("%d ", ((Int *)element)->value);
}

void double_to_string(void *element)
{
    printf("%lf ", ((Double *)element)->value);
}

void float_to_string(void *element)
{
    printf("%f ", ((Float *)element)->value);
}

void complex_to_string(void *element)
{
    complex_print(((MyComplexWrapper *)element)->value);
}

FieldInfo *getIntegerFieldInfo()
{
    if (!INT_FIELD_INFO)
    {
        INT_FIELD_INFO = malloc(sizeof(FieldInfo));
        INT_FIELD_INFO->element_size = sizeof(Int);
        INT_FIELD_INFO->toString = int_to_string;
    }
    return INT_FIELD_INFO;
}

FieldInfo *getDoubleFieldInfo()
{
    if (!DOUBLE_FIELD_INFO)
    {
        DOUBLE_FIELD_INFO = malloc(sizeof(FieldInfo));
        DOUBLE_FIELD_INFO->element_size = sizeof(Double);
        DOUBLE_FIELD_INFO->toString = double_to_string;
    }
    return DOUBLE_FIELD_INFO;
}

FieldInfo *getFloatFieldInfo()
{
    if (!FLOAT_FIELD_INFO)
    {
        FLOAT_FIELD_INFO = malloc(sizeof(FieldInfo));
        FLOAT_FIELD_INFO->element_size = sizeof(Float);
        FLOAT_FIELD_INFO->toString = float_to_string;
    }
    return FLOAT_FIELD_INFO;
}

FieldInfo *getComplexFieldInfo()
{
    if (!COMPLEX_FIELD_INFO)
    {
        COMPLEX_FIELD_INFO = malloc(sizeof(FieldInfo));
        COMPLEX_FIELD_INFO->element_size = sizeof(MyComplexWrapper);
        COMPLEX_FIELD_INFO->toString = complex_to_string;
    }
    return COMPLEX_FIELD_INFO;
}

Int *integer(int value)
{
    Int *res = malloc(sizeof(Int));
    res->value = value;
    return res;
}

Double *double_(double value)
{
    Double *res = malloc(sizeof(Double));
    res->value = value;
    return res;
}

Float *float_(float value)
{
    Float *res = malloc(sizeof(Float));
    res->value = value;
    return res;
}

MyComplexWrapper *complex_(float real, float imag)
{
    MyComplexWrapper *c = malloc(sizeof(MyComplexWrapper));
    c->value.real = real;
    c->value.imag = imag;
    return c;
}

Int *intSum(Int *a, Int *b)
{
    Int *r = malloc(sizeof(Int));
    r->value = a->value + b->value;
    return r;
}

Double *doubleSum(Double *a, Double *b)
{
    Double *r = malloc(sizeof(Double));
    r->value = a->value + b->value;
    return r;
}

Float *floatSum(Float *a, Float *b)
{
    Float *r = malloc(sizeof(Float));
    r->value = a->value + b->value;
    return r;
}

MyComplexWrapper *complexSum(MyComplexWrapper *a, MyComplexWrapper *b)
{
    MyComplexWrapper *r = malloc(sizeof(MyComplexWrapper));
    MyComplex tmp = complex_add(a->value, b->value);
    r->value = tmp;
    return r;
}

Int *intPoduct(Int *a, Int *b)
{
    Int *r = malloc(sizeof(Int));
    r->value = a->value * b->value;
    return r;
}

Double *doubleProduct(Double *a, Double *b)
{
    Double *r = malloc(sizeof(Double));
    r->value = a->value * b->value;
    return r;
}

Float *floatProduct(Float *a, Float *b)
{
    Float *r = malloc(sizeof(Float));
    r->value = a->value * b->value;
    return r;
}

MyComplexWrapper *complexProduct(MyComplexWrapper *a, MyComplexWrapper *b)
{
    MyComplexWrapper *r = malloc(sizeof(MyComplexWrapper));
    MyComplex tmp = complex_mul(a->value, b->value);
    r->value = tmp;
    return r;
}

void *sum(FieldInfo *type, void *a, void *b)
{
    if (type == getIntegerFieldInfo())
        return intSum(a, b);
    if (type == getDoubleFieldInfo())
        return doubleSum(a, b);
    if (type == getFloatFieldInfo())
        return floatSum(a, b);
    if (type == getComplexFieldInfo())
        return complexSum(a, b);
    return NULL;
}

void *product(FieldInfo *type, void *a, void *b)
{
    if (type == getIntegerFieldInfo())
        return intPoduct(a, b);
    if (type == getDoubleFieldInfo())
        return doubleProduct(a, b);
    if (type == getFloatFieldInfo())
        return floatProduct(a, b);
    if (type == getComplexFieldInfo())
        return complexProduct(a, b);
    return NULL;
}

void *Zero(FieldInfo *type)
{
    void *z = malloc(type->element_size);
    memset(z, 0, type->element_size);
    return z;
}
