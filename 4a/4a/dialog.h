#ifndef DIALOG_H
#define DIALOG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct  Node Node;


int D_Add(Node** tree);
int D_Find(Node** tree);
int D_Delete(Node** tree);
int D_Show(Node** tree);
int D_Sort(Node** tree);
int D_FindUniq(Node** tree);
int dialog(const char* msgs[], int N);
int D_Dot(Node** tree);
int D_Timing(Node **);
int D_Dop(Node** tree);


#endif
