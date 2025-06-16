#ifndef T2_H
#define T2_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct info info;
typedef struct Node Node;
typedef struct KeySpace KeySpace;
typedef struct Table Table;
typedef KeySpace* iterator;

char *myreadline();
int printTable(Table* table);
iterator searchTable(Table* table, char* key);
int  copy(Table* table, void* key);
iterator push(Table** table, void* key, void* data);
iterator pop(iterator i, iterator end, Table* table);
void* individual1(Table* table, void* key, int release);
void removeTable(Table* t);
int poprelease(Table* t, char* key, int release);
char* myread(FILE* f, char* str);
void* intxt(Table** table);
int getInt(int* num, const char* pr);
void menu(Table* table, Table* new);


#endif
