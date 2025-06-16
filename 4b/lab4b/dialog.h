#ifndef DIALOG_H
#define DIALOG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data data;
typedef struct answ answ;
typedef struct  node node;


int D_Add(node**);
int D_Add2(node**);
int D_Find(node**);
int D_Delete(node**);
int D_Show(node**);
int D_Sort(node**);
int D_FindUniq(node**);
int dialog(const char* msgs[], int N);
int D_Dot(node**);
int D_Timing(node**);
int D_Dop(node**);
int delete(node** tree, char* key);
int insert(node** tree, char* key, int info);
int Fileread(node** tree);
char* myread(FILE* f, char* line1);
char *myreadline();
int Filereaddop();


#endif
