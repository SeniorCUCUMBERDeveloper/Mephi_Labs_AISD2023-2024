#ifndef DOPFUNC_H
#define DOPFUNC_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Pair
{
        int* offsets_f;
}Pair;


int max(int seek, int seekNxt, FILE* f, int* indexmax);
int min(int a, int b);
int input(FILE* f, Pair* pair);
int addTask(FILE* f, FILE* f2,  Pair* pair, int lenmatrix);
int file(Pair* pair);
void printBin(int count);


#endif
