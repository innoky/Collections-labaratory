typedef struct
{
    double real;
    double img;
} complex;

complex* new_complex(double real, double img);
complex *complex_add(complex *a, complex *b);
complex *complex_sub(complex *a, complex *b);
complex *complex_mul(complex *a, complex *b);

void complex_print(complex *a);
void complex_free(complex *a);
