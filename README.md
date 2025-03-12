# Collections labaratory

![LabaMatrix Logo](https://nvpk-mephi.ru/wp-content/uploads/2021/09/3ddda32c713589b65cd686fddb280b3f.png)

LabaMatrix - это библиотека для работы с матрицами в языке программирования C. Она поддерживает различные типы данных, включая целые числа, числа с плавающей запятой и комплексные числа. Библиотека предоставляет функции для создания, заполнения, сложения, умножения, транспонирования матриц и добавления линейных комбинаций строк.

## Содержание

- [Установка](#установка)
- [Использование](#использование)
- [Функции](#функции)
- [Примеры](#примеры)
- [Сборка](#сборка)
- [Лицензия](#лицензия)

## Установка

Склонируйте репозиторий на ваш локальный компьютер:

```bash
git clone https://github.com/yourusername/LabaMatrix.git
cd LabaMatrix
```

## Использование
Подключите заголовочные файлы matrix.h и complex.h в вашем проекте:
```c
#include "matrix.h"
#include "complex.h"
```
## Функции
__Создание матрицы__
```c
matrix_t* matrix_create(int rows, int cols, int type);
```
__Заполнение матрицы__
```c
void matrix_fill(matrix_t *m, void* value, int type);
```
__Установка значений в матрице__
```c
void matrix_set(matrix_t *m, int row, int col, void* value);
```
__Сложение матриц__
```c
matrix_t* matrix_sum(matrix_t *a, matrix_t *b);
```
__Умножение матриц__
```c
matrix_t* matrix_mul(matrix_t *a, matrix_t *b);
```
__Транспонирование матрицы__
```c
matrix_t* transpose(matrix_t *m);
```
__Добавление линейной комбинации строк__
```c
matrix_t* add_linnear_comb(matrix_t* m, int row, void* coef);
```
__Уничтожение матрицы__
```c
void matrix_destroy(matrix_t *m);
```
__Печать матрицы__
```
void matrix_print(matrix_t *m, short int BPrint);
```
## Примеры
Пример использования библиотеки:
```c
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "complex.h"

int main() {
    // Matrix creation
    MATRIX(m1, 3, 4, complex);
    MATRIX(m2, 3, 4, complex);
    MATRIX(m3, 4, 3, complex);

    // Matrix filling / setting (with Complex) and printing
    Complex(c1, 3.3, 4);
    Complex(c_f, 45.3, 2.4);
    matrix_fill(m1, c1, 2);
    matrix_set(m1, 1, 3, c_f);
    printf("Filled matrix:\n");
    matrix_print(m1, 0);

    // Matrix summation and printing
    Complex(c2, 3, 4);
    matrix_fill(m2, c2, 2);
    matrix_t* sum_matrix = matrix_sum(m1, m2);
    printf("Summed matrices:\n");
    matrix_print(sum_matrix, 0);

    // Matrix multiply and printing
    Complex(c3, 5, 2);
    matrix_fill(m3, c3, 2);
    matrix_t* mul_matrix = matrix_mul(sum_matrix, m3);
    printf("Multiplied matrices:\n");
    matrix_print(mul_matrix, 0);

    // Matrix transpose and printing
    matrix_t* trans_matrix = transpose(mul_matrix);
    printf("Transposed matrix:\n");
    matrix_print(trans_matrix, 1);

    // Linear combination adding
    Complex(coef, 5, 12);
    matrix_t* lin_added_matrix = add_linnear_comb(trans_matrix, 0, coef);
    matrix_print(lin_added_matrix, 0);

    return 0;
}
```
## Сборка
Для сборки проекта используйте Makefile. Выполните команду:
```bash
make
```
Для очистки скомпилированных файлов:
```bash
make clean
```
## Лицензия
Этот проект лицензирован под лицензией MIT. Подробности см. в файле LICENSE.
