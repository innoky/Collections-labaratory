typedef struct
{
    float real;
    float img;
} MyComplex;

MyComplex* new_complex(float real, float img);
MyComplex *complex_add(MyComplex *a, MyComplex *b);
MyComplex *complex_sub(MyComplex *a, MyComplex *b);
MyComplex *complex_mul(MyComplex *a, MyComplex *b);
int complex_equals(MyComplex *a, MyComplex *b);

void complex_print(MyComplex *a);
void complex_free(MyComplex *a);
