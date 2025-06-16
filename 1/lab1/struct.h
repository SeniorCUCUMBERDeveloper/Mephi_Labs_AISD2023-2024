#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct String
{
    int len;
    int* array;
}String;

typedef struct Matrix
{
    int strings;
    String* matr;
}Matrix;

#endif
