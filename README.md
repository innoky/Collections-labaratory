# Collections labaratory

![LabaMatrix Logo](https://nvpk-mephi.ru/wp-content/uploads/2021/09/3ddda32c713589b65cd686fddb280b3f.png)

Collections labaratory - это библиотека для работы с матрицами в языке программирования C созданная в ходе выполнения лабараторной работы по курсу _"Полиморфные и абстрактные типы данных"_. Она поддерживает различные типы данных, включая целые числа, числа с плавающей запятой и комплексные числа. Библиотека предоставляет функции для создания, заполнения, сложения, умножения, транспонирования матриц и добавления линейных комбинаций строк.

## Содержание

- [Установка](#установка)
- [Использование](#использование)
- [Функции](#функции)
- [Макросы](#макросы)
- [Примеры](#примеры)
- [Тесты](#тесты)
- [Сборка](#сборка)
- [Лицензия](#лицензия)

## Установка

Склонируйте репозиторий на ваш локальный компьютер:

```bash
git clone https://github.com/yourusername/LabaMatrix.git
cd LabaMatrix
```

## Использование
Подключите заголовочные файлы matrix.h и MyComplex.h в вашем проекте:
```c
#include "matrix.h"
#include "MyComplex.h"
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
matrix_t* matrix_transpose(matrix_t *m);
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
```c
void matrix_print(matrix_t *m, short BPrint);
```

## Макросы
_Библиотека поддерживает несколько удобных макросов._<br><br>
__=== СОЗДАНИЕ МАТРИЦЫ ===__
<br>
```c
MATRIX(name, rows, cols, type)
```
Создание новой матрицы размером _rows * cols_ типа _type_ с именем _name_
<br><br>
__=== ЗАПОЛНЕНИЕ МАТРИЦЫ ===__
```c
MFILL(name, value, type)
```
Заполнение матрицы с именем _name_ значением _value_ с указанным типом _type_
<br><br>
__=== УСТАНОВКА ЗНАЧЕНИЯ ===__
```c
MSET(name, row, col, value)
```
Установка значения в матрицу _name_ по указанной строке _row_ и столбцу _col_ значением _value_
<br><br>
__=== СОЗДАНИЕ КОМПЛЕКСНОГО ЧИСЛА ===__
```c
COMPLEX(name, real, img)
```
Создание комплексного числа _name_ с действительной частью _real_ и мнимой частью _img_
<br><br>
__=== ВЫВОД МАТРИЦЫ ===__
```c
MPRINT(matrix, BPrint)
```
Вывод матрицы _matrix_ в терминал. Аргумент BPrint принимает либо нуль, либо единицу. При аргументе _0_ происходит обычный вывод матрицы, при _1_ - стилизованный боковыми скобками.
<br><br>
## Примеры
Пример использования библиотеки:
```c
#include <stdio.h>
#include <stdlib.h>

#include "DataType.h"
#include "matrix.h"
#include "MyComplex.h"


int main() {
    // // Matrix creation
    MATRIX(m1, 3, 4, cmp);
    MATRIX(m2, 3, 4, cmp);
    MATRIX(m3, 4, 3, cmp);

    // Matrix filling / setting (with COMPLEX) and printing
    COMPLEX(c1, 3.3, 4);
    COMPLEX(c_f, 45.3, 2.4);
    MFILL(m1, c1, cmp);
    MSET(m1,1,3,c_f);
    printf("Filled matrix:\n");
    matrix_print(m1, 0);

    // Matrix summation and printing
    COMPLEX(c2, 3, 4);
    MFILL(m2, c2, cmp);
    matrix_t* sum_matrix = matrix_sum(m1, m2);
    printf("Summed matrices:\n");
    matrix_print(sum_matrix, 0);

    //Matrix muliply and printing
    COMPLEX(c3, 5, 2);
    MFILL(m3, c3, cmp);
    matrix_t* mul_matrix = matrix_mul(sum_matrix, m3);
    printf("Multiplied matrices:\n");
    matrix_print(mul_matrix, 0);

    //Matrix transpose and printing
    matrix_t* trans_matrix = matrix_transpose(mul_matrix);
    printf("Transposed matrix:\n");
    matrix_print(trans_matrix, 1);

    //Linear combination adding
    COMPLEX(coef, 5, 12);
    matrix_t* lin_added_matrix = add_linnear_comb(trans_matrix, 0, coef);
    matrix_print(lin_added_matrix, 0);

    return 0;
}
```
## Тесты
_Под данную библиотеку написаны Unit тесты на базе среды тестирования [Unity](https://github.com/ThrowTheSwitch/Unity):_
```c
void test_matrix_sum_int() ...;
void test_matrix_sum_float() ...;
void test_matrix_sum_complex() ...;

void test_matrix_mul_int() ...;
void test_matrix_mul_float() ...;
void test_matrix_mul_complex() ...;

void test_matrix_transpose_int() ...;
void test_matrix_transpose_float() ...;
void test_matrix_transpose_complex() ...;

void test_matrix_add_linnear_comb_int() ...;
void test_matrix_add_linnear_comb_float() ...;
void test_matrix_add_linnear_comb_complex() ...;
```
## Сборка
Для сборки main файла с примерами использования используйте Makefile. Выполните команду и запустите:
```bash
make main.exe
./main
```
Для сборки Unit тестов используйте Makefile. Выполните команду и запустите:
```bash
make tests\UnitTests.exe
cd tests
./UnitTests
```
Для очистки скомпилированных файлов:
```bash
make clean
```
## Лицензия
Этот проект лицензирован под лицензией MIT. Подробности см. в файле LICENSE.
