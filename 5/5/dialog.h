#ifndef DIALOG_H
#define DIALOG_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Graph Graph;
char *myreadline();
int getInt(int* num, const char* pr);
int dialog(const char* msgs[], int N);
int D_Add_V(Graph* G);
int D_Add_E(Graph* G);
int D_Show(Graph* G);
int D_Delete_E(Graph* G);
int D_Delete_V(Graph* G);
int D_Matrix(Graph* G);
int D_Path(Graph* G);
int D_DFS(Graph* G);
int D_CC(Graph* G);
int D_Correct(Graph* G);
int D_Dot(Graph* G);
int D_Primer(Graph* G);
int D_Dop1(Graph* G);
int D_Dop2(Graph* G);
int D_Dop3(Graph* G);
int D_Gen(Graph* G);

#endif
