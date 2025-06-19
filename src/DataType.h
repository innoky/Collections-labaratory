#ifndef DATATYPE_H
#define DATATYPE_H

#include <stddef.h>
#include "MyComplex.h"

typedef struct
{
  void (*multiply)(const void* a, const void* b, void* c);
  void (*sum)(const void* a, const void* b, void* c);
  size_t size;
} DataTypeOperations;

extern const DataTypeOperations int_ops;
extern const DataTypeOperations double_ops;
extern const DataTypeOperations complex_ops;


#endif 
