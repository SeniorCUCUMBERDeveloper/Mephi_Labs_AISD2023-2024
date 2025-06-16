#ifndef T_H
#define T_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct info info;
typedef struct Node Node;
typedef struct KeySpace KeySpace;
typedef struct Table Table;


char *myreadline();
int printTable(Table* table);
int searchTable(Table* table, char* key);
int  copy(Table* table, void* key);
int push(Table** table, void* key, void* data);
int pop(Table* table, void* key);
void* individual1(Table* table, void* key, int release);
void removeTable(Table* t);
int poprelease(Table* t, char* key, int release);
char* myread(FILE* f, char* str);
void* intxt(Table** table);
int getInt(int* num, const char* pr);
void menu(Table* table, Table* new);
/*
int D_Add(Table** table);
int D_Find(Table** table);
int D_Delete(Table** table);
int D_Show(Table** table);
int D_Import(Table** table);
int D_New(Table** table);
int D_Remove(Table** table);
int dialog(const char* msgs[], int N);*/


#endif
