#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data data;
typedef struct queue queue;
typedef struct Airport Airport;


void freequeue(queue* q);
void InputAirport(Airport** mass, int num);
void freeAirport(Airport* mass, int num);
void Input();
void put(queue* q, void* data);
void*  pop(queue* q);
char *myreadline();
char* inputKeyBoard(queue* Time, int* len, int* num);
void printq(queue* q, int flag);
void bubbleSort(queue* q, int len);
Airport* individualTask(queue* Time, Airport* mass, int num, int len);
data* makedata(char* str, int x, int y);


#endif
