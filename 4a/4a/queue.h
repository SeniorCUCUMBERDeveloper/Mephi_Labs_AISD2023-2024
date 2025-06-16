#ifndef QUEUE_H
#define QUEUE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Info Info;
typedef struct Stack Stack;
typedef struct Node Node;


void add(Stack* stack, Node* x);
Node* del(Stack* stack);


#endif
