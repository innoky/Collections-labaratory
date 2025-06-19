#include "DataType.h"
#include <string.h>

// INT OPERATIONS
static void int_multiply(const void* a, const void* b, void* c) {
    *(int*)c = (*(int*)a) * (*(int*)b);
}

static void int_sum(const void* a, const void* b, void* c) {
    *(int*)c = (*(int*)a) + (*(int*)b);
}

const DataTypeOperations int_ops = {
    .multiply = int_multiply,
    .sum = int_sum,
    .size = sizeof(int)
};


// DOUBLE OPERATIONS
static void double_multiply(const void* a, const void* b, void* c) {
    *(double*)c = (*(double*)a) * (*(double*)b);
}

static void double_sum(const void* a, const void* b, void* c) {
    *(double*)c = (*(double*)a) + (*(double*)b);
}

const DataTypeOperations double_ops = {
    .multiply = double_multiply,
    .sum = double_sum,
    .size = sizeof(double)
};


// COMPLEX OPERATIONS
static void complex_multiply(const void* a, const void* b, void* c) {
    MyComplex* result = (MyComplex*)c;
    const MyComplex* comp_a = (const MyComplex*)a;
    const MyComplex* comp_b = (const MyComplex*)b;
    result->real = comp_a->real * comp_b->real - comp_a->imag * comp_b->imag;
    result->imag = comp_a->real * comp_b->imag + comp_a->imag * comp_b->real;
}

static void complex_sum(const void* a, const void* b, void* c) {
    MyComplex* result = (MyComplex*)c;
    const MyComplex* comp_a = (const MyComplex*)a;
    const MyComplex* comp_b = (const MyComplex*)b;
    result->real = comp_a->real + comp_b->real;
    result->imag = comp_a->imag + comp_b->imag;
}

const DataTypeOperations complex_ops = {
    .multiply = complex_multiply,
    .sum = complex_sum,
    .size = sizeof(MyComplex)
};
