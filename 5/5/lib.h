#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000

typedef struct Edge Edge;
typedef struct Point Point;
typedef struct Graph Graph;
typedef struct reb reb;

Graph* create();
Edge* put(Edge* smez, Point* vericales, int weight);
Edge* pop(Edge* smez, Edge* x);
int addVertex(Graph* G, char* key);
int addEdges(Graph* G, char* from, char* to, int weight);
void printGraph(Graph* G);
int deleteEdge(Graph* G, char* from, char* to);
int deleteVerticals(Graph** G, char* from);
int** matr(Graph* G);
void printMatrix(int** matrix, int n);
int path(Graph* G,  int from, FILE* f, FILE* f2);
void DFS(Point* start, int* visited);
void findConnectedComponents(Graph* G);
void destroyGraph(Graph** G);
int New_name(Graph* G, char* name, char* new);
void deleteMatr(int** matrix, int n);
int indot(Graph* G);
void dop1(Graph* G);
void dop2(Graph* G);
void dop3(Graph* G);
void deleteALLVer(Graph* G);


#endif
