#pragma once

#include <stdlib.h>
#include "MyComplex.h"

typedef struct MyComplexWrapper
{
    MyComplex value;
} MyComplexWrapper;

typedef struct FieldInfo
{
    size_t element_size;
    void (*toString)(void *element);
} FieldInfo;

// === Структуры обёртки ===

typedef struct
{
    int value;
} Int;

typedef struct
{
    double value;
} Double;

typedef struct
{
    float value;
} Float;


// === Геттеры FieldInfo ===

FieldInfo *getIntegerFieldInfo();
FieldInfo *getDoubleFieldInfo();
FieldInfo *getFloatFieldInfo();
FieldInfo *getComplexFieldInfo();

// === Универсальные арифметические операции ===

void *Zero(FieldInfo *type);
void *sum(FieldInfo *type, void *arg1, void *arg2);
void *product(FieldInfo *type, void *arg1, void *arg2);

// === Инициализация значений ===

Int *integer(int value);
Double *double_(double value);
Float *float_(float value);
MyComplexWrapper *complex_(float real, float imag);

// === Арифметика ===

Int *intSum(Int *a, Int *b);
Int *intPoduct(Int *a, Int *b);

Double *doubleSum(Double *a, Double *b);
Double *doubleProduct(Double *a, Double *b);

Float *floatSum(Float *a, Float *b);
Float *floatProduct(Float *a, Float *b);

MyComplexWrapper *complexSum(MyComplexWrapper *a, MyComplexWrapper *b);
MyComplexWrapper *complexProduct(MyComplexWrapper *a, MyComplexWrapper *b);

// === toString ===

void int_to_string(void *element);
void double_to_string(void *element);
void float_to_string(void *element);
void complex_to_string(void *element);
