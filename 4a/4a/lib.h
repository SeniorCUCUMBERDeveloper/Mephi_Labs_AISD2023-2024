#ifndef LIB_H
#define LIB_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node Node;
typedef struct answ answ;


Node* createNode(int key, char* info);
Node* MiNode(Node* tree);
char* push(Node** tree, int key, char* info);
Node* searchPrev(Node* current, int key);
void printTree(Node *tree, int depth);
int pop(Node** tree, int key);
int sorted(Node* tree, int key);
char* search(Node* tree, int key);
answ* uniqsearch(Node* tree, int key, answ* arr);
int indot(Node* tree);
int deleted(Node** t);
int searchFORtiming(Node* tree, int key);
int Fileread(Node** tree);
char* myread(FILE* f, char* line1);
int sorted_b(Node* tree);


#endif
