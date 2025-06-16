#ifndef T_H
#define T_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>



typedef struct KeySpace KeySpace;
typedef struct Table Table;
typedef struct ans ans;


void massiveCorrect(int* array, int i, int count);
int getInt(int* num, const char* pr);
int deleteTable(Table** table);
int printTable(Table* table);
int hash(char* str, int del);
int push(Table** table, char* key, char* data);
int find(Table* table, char* key);
int poprelease(Table** table, char* key, int release);
int correctTable(Table** table, char* key, int release, int j);
int allpop(Table** table, char* key);
ans* findALLkey(Table* table, char* key);
char** findRelease(Table* table, char* key, int realese);
int fwritebin(Table* table);
int freadbin(Table** table);
char *myreadline();
int copy(Table* tabke, char* key);
int UpdateTable(Table** table, int new_size);
int searchNexteasy(Table** table);
int ratio(Table* table);


#endif
