#include "lib.h"
#include <time.h>



typedef struct Edge{
    struct Point* Verticals;
    int weight;
    struct Edge* next;
}Edge;


typedef struct Point{
    int index;
    char* name;
    Edge* smez;
}Point;



typedef struct Graph {
    int n;
    Point** points;
} Graph;



typedef struct reb{
    int from;
    int to;
    int w;
}reb;


Graph* create(){
	Graph* T = malloc(sizeof(Graph));
	T->n = 0;
	T->points = NULL;
	return T;
}


Edge* put(Edge* smez, Point* vericales, int weight)
{
    Edge* ptr = malloc(sizeof(Edge));
    ptr->Verticals = vericales;
    ptr->weight = weight;
    ptr->next = NULL;
    if (smez == NULL)
    {
        smez = ptr;
    }
    else
    {
        Edge* cur = smez;
        Edge* prev = smez;
        while(cur != NULL && cur->Verticals->index < vericales->index){
            prev = cur;
            cur = cur->next;
        }
        if(cur != NULL && cur->Verticals->index == vericales->index){
            cur->weight = weight; 
            free(ptr);
            return smez;
        }
        if(prev != cur){
            ptr->next = cur;
            prev->next = ptr;
        }else{
            ptr->next = cur;
            smez = ptr;
        }
    }
    return smez;
}


Edge* pop(Edge* smez, Edge* x){
    if(smez == NULL){
        return smez;
    }
    if(smez == x){
        smez = x->next;
        free(x);
    }else{
        Edge* cur = smez;
        while(cur->next != x){
            cur = cur->next;
        }
        cur->next = x->next;
        free(x);
    }
    return smez;
}


int addVertex(Graph* G, char* key){
    if(G->points == NULL){
        G->n++;
        G->points = malloc(sizeof(Point*) * G->n);
        G->points[0] = malloc(sizeof(Point));
        G->points[0]->index = G->n - 1;
        G->points[0]->name = key;
        G->points[0]->smez = NULL;
        return 1;
    }
    for(int i = 0; i < G->n; i++){
        if(strcmp(key, G->points[i]->name) == 0){
            return -1;
        }
    }
    G->n++;
    G->points = realloc(G->points, G->n * sizeof(Point*));
    G->points[G->n - 1] = malloc(sizeof(Point));
    G->points[G->n - 1]->index = G->n - 1;
    G->points[G->n - 1]->name = key;
    G->points[G->n - 1]->smez = NULL;
    return 1;
}


int addEdges(Graph* G, char* from, char* to, int weight){
    if(G->points == NULL){
        return -1;
    }
    int from_v = -1;
    Point* to_v = NULL;
    for(int i = 0; i < G->n; i++){
        if(strcmp(from, G->points[i]->name) == 0){
            from_v = i;
         }
         if(strcmp(to, G->points[i]->name) == 0){
            to_v = G->points[i];
         }
    }
    if(from_v == -1 || to_v == NULL){
        return -1;
    }
    G->points[from_v]->smez = put(G->points[from_v]->smez, to_v,  weight);
    return 1;
}


void printGraph(Graph* G){
    for(int i = 0; i < G->n; i++){
        printf("%d: %s -> ", G->points[i]->index, G->points[i]->name);
        Edge* ptr = G->points[i]->smez;
        while(ptr != NULL){
            printf("%d:%s  <->  ", ptr->Verticals->index, ptr->Verticals->name);
            ptr = ptr->next;
        }
        printf("NULL");
        printf("\n");
    }
}


int deleteEdge(Graph* G, char* from, char* to){
    int from_v = -1;
    for(int i = 0; i < G->n; i++){
        if(strcmp(from, G->points[i]->name) == 0){
            from_v = i;
            break;
        }
    }
    if(from_v == -1){
        return -1;
    }
    Edge* e = G->points[from_v]->smez;
    while(e != NULL && strcmp(e->Verticals->name, to) != 0){
        e = e->next;
    }
    if(e == NULL){
        return -1;
    }
    G->points[from_v]->smez = pop(G->points[from_v]->smez, e);
    return 1;
}


int deleteVerticals(Graph** G, char* from){
    int from_v = -1;
    for(int i = 0; i < (*G)->n; i++){
        if(strcmp(from, (*G)->points[i]->name) == 0){
            from_v = i;
            break;
        }
    }
    if(from_v == -1){
        return -1;
    }
    for(int i = 0; i < (*G)->n; i++){
        deleteEdge(*G, from, (*G)->points[i]->name);
        deleteEdge((*G), (*G)->points[i]->name, from);
    }
    free((*G)->points[from_v]->name);
    free((*G)->points[from_v]->smez);
    Point* del = (*G)->points[from_v];
    (*G)->n--;
    for(int i = from_v; i < (*G)->n; i++){
        (*G)->points[i] = (*G)->points[i + 1];
        (*G)->points[i + 1]->index--;
    }
    free(del);
    if((*G)->n == 0){
        free((*G)->points);
        (*G)->points = NULL;
        return 1;
    }
    (*G)->points = realloc((*G)->points, (*G)->n * sizeof(Point*));
    return 1;
}


int** matr(Graph* G){
    if(G == NULL){
        return NULL;
    }
    int * * matrix = (int * *) malloc(sizeof(int *) * G->n);
    for (int i = 0; i < G->n; i++) {
        matrix[i] = (int *) malloc(sizeof(int) * G->n);
        for (int j = 0; j < G->n; j++) {
            matrix[i][j] = INF;
        }
    }
    for(int i = 0; i < G->n; i++){
        Edge* ptr = G->points[i]->smez;
        while(ptr != NULL){
            matrix[G->points[i]->index][ptr->Verticals->index] = ptr->weight;
            ptr = ptr->next;
        }
    }
    return matrix;
}


void printMatrix(int** matrix, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INF){
                printf("INF\t");
            }else{
                printf("%d\t", matrix[i][j]);
            }
        }
        printf("\n");
    }
}


void belmanFord(Graph* G,  reb* list, int* distance, int* parent, int countEdges){
	for(int i = 0; i < G->n - 1; i++){
	    for(int j = 0; j < countEdges; j++){
	        if(distance[list[j].to] > distance[list[j].from] + list[j].w){
	            distance[list[j].to] = distance[list[j].from] + list[j].w;
	            parent[list[j].to] = list[j].from;
	        }
	    }
	}
}

char* color();

int path(Graph* G,  int from, FILE* f, FILE* f2){
    if(G == NULL){
        return 1;
    }
    srand(time(NULL));
    int countEdges = 0;
    for(int i = 0; i < G->n; i++){
        Edge* ptr = G->points[i]->smez; 
        while(ptr != NULL){
            countEdges++;
            ptr = ptr->next;
        }
    }
    
    reb* list = malloc(countEdges * sizeof(reb));
    int k = 0;
    for(int i = 0; i < G->n; i++){
        Edge* ptr = G->points[i]->smez;
        while(ptr != NULL){
                reb l;
                l.from = G->points[i]->index;
                l.to = ptr->Verticals->index;
                l.w = ptr->weight;
                list[k] = l;
                k++;
                ptr = ptr->next;
        }
    }


    int* parent = malloc(G->n  * sizeof(int));
    for(int i = 0; i < G->n; i++){
        parent[i] = -1;
    }
    int* distance = malloc(G->n * sizeof(int));
    for(int i = 0; i < G->n; i++){
        distance[i] = INF;
    }
    distance[from] = 0;
    belmanFord(G, list, distance, parent, countEdges);
    for(int i = 0; i < G->n - 1; i++){
        for(int j = 0; j < countEdges; j++){
            if(distance[list[j].to] > distance[list[j].from] + list[j].w){
                return 1;
            }
        }
    }
    
    char* c = NULL;
    for(int i = 0; i < G->n; i++){
        int cur = i;
        printf("%d -> %d Shortest path = %d\n",from, i, distance[cur]);
        printf("END<-  ");
        if(f != NULL){
        	c = color();
        	fprintf(f2, "%d->%d: %d\n", from, i, distance[cur]);
        	fprintf(f2, "End ");
        	fprintf(f, "\t%d[color=\"%s\"][xlabel = \"%d\"];\n", cur, c, distance[cur]);
        }
        while(cur != -1){
            printf("%d ", cur);
            int next = cur;
            cur = parent[cur];
            if(cur != -1){
            	fprintf(f2, "%d ", cur);
            	fprintf(f, "\t%d->%d[style=\"dotted\"][color=\"%s\"];\n", cur, next, c);
            }
        }
        if(f != NULL && c != NULL){
        	fprintf(f2, "Begin\n");
        	free(c);
        }
        printf("  <-BEGIN");
        printf("\n");
    }
    free(parent);
    free(distance);
    free(list);
    return 0;
}



void DFS(Point* vertex, int* massive) {
    massive[vertex->index] = 1;
    printf("Visited: %s\n", vertex->name);
    Edge* edge = vertex->smez;
    while (edge != NULL) {
        if (massive[edge->Verticals->index] == 0) {
            DFS(edge->Verticals, massive);
        }
        edge = edge->next;
    }
}


void findConnectedComponents(Graph* G) {
    int* mass = calloc(G->n, sizeof(int));
    for (int i = 0; i < G->n; i++) {
        if (mass[i] == 0) {
            printf("Connected Component: \n");
            DFS(G->points[i], mass);
            printf("\n");
        }
    }
    free(mass);
}


void destroyGraph(Graph** G){

    for(int i = 0; i < (*G)->n; i++){
        deleteVerticals(&*G, (*G)->points[i]->name);
        i--;
    }
    free(*G);
    return;
}


int New_name(Graph* G, char* name, char* new){
    int index = -1;
    for(int i = 0; i < G->n; i++){
        if(strcmp(name, G->points[i]->name) == 0){
            index = i;
            break;
        }
    }
    if(index == -1){
        return -1;
    }
    free(G->points[index]->name);
    G->points[index]->name = new;
    return 1;
}


void deleteMatr(int** matrix, int n){
    for(int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
}



int indot(Graph* G){
    FILE* file = fopen("output.dot", "w");
    fprintf(file, "digraph G {\n");
    fprintf(file, "\tnode [style=filled];\n");
    for(int i = 0; i < G->n; i++){
        fprintf(file,"\t%d;\n", G->points[i]->index);
    }
    for(int i = 0; i < G->n; i++){
        Edge* ptr = G->points[i]->smez;
        while(ptr!=NULL){
                fprintf(file, "\t%d->%d[xlabel=\"%d\"];\n", G->points[i]->index, ptr->Verticals->index, ptr->weight);
                ptr = ptr->next;
        }
    }
    fprintf(file, "}\n");
    fclose(file);
    return 0;
}


void DFS1(Point* vertex, int* massive, FILE* f, FILE* f2,  char* s){
   massive[vertex->index] = 1;
   fprintf(f, "\t%d[color=\"%s\"];\n", vertex->index, s);
   fprintf(f2, "%d\n", vertex->index);
    Edge* edge = vertex->smez;
    while (edge != NULL) {
        if (massive[edge->Verticals->index] == 0) {
        		fprintf(f, "\t%d->%d[style=\"dotted\"][color=\"%s\"];\n", vertex->index, edge->Verticals->index, s);
            DFS1(edge->Verticals, massive, f, f2, s);
        }
        edge = edge->next;
    }
}

char* color(){
	char symb[] = "0123456789ABCDEF";
	char* str = calloc(8, sizeof(char));
	str[0] = '#';
	int i = 1;
	while(i < 7)
	{
		int index = rand() % strlen(symb);
		str[i] =symb[index];
		i++;
	}
	str[7] = '\0';
	return str;
}


void dop1(Graph* G){
	srand(time(NULL));
	char* ch =  "#FF0000";
    char mch[1];
    indot(G);
    FILE* file = fopen("output.dot", "r+");
    FILE* f = fopen("res1.txt", "w");
    fseek(file, 0, SEEK_END);
    fseek(file, -1, SEEK_CUR);
    fseek(file, -1, SEEK_CUR);
    ch = fgets(mch, sizeof(char), file);
    printf("input number of vertex\n");
    int d;
    ch = "#FF0000";
    scanf("%d", &d);
    fprintf(f, "start %d:\n", d);
    int* massive = calloc(G->n, sizeof(int));
    DFS1(G->points[d], massive, file, f, ch);
    fprintf(file, "}\n");
    fclose(file);
    fclose(f);
    system("dot -Tpng output.dot -o output.png");
    system("catimg output.png");
    free(massive);
    return;
}


void dop2(Graph* G) {
	srand(time(NULL));
    int* mass = calloc(G->n, sizeof(int));
    char* ch;
    char mch[1];
    indot(G);
    FILE* file = fopen("output.dot", "r+");
    FILE* f = fopen("res2.txt", "w");
    fseek(file, 0, SEEK_END);
    fseek(file, -1, SEEK_CUR);
    fseek(file, -1, SEEK_CUR);
    ch = fgets(mch, sizeof(char), file);
    for (int i = 0; i < G->n; i++) {
        if (mass[i] == 0) {
        	fprintf(f, "CC:\n");
        	ch = color();
            DFS1(G->points[i], mass, file,f,  ch);
            free(ch);
        }
    }
    fprintf(file, "}\n");
    free(mass);
    fclose(file);
    fclose(f);
    system("dot -Tpng output.dot -o output.png");
    system("catimg output.png");
    return;
}


void dop3(Graph* G){
	char* ch;
    char mch[1];
    indot(G);
    FILE* file = fopen("output.dot", "r+");
    FILE* f = fopen("res3.txt", "w");
    fseek(file, 0, SEEK_END);
    fseek(file, -1, SEEK_CUR);
    fseek(file, -1, SEEK_CUR);
    ch = fgets(mch, sizeof(char), file);
    printf("Input from-vertex\n");
    int d;
    scanf("%d", &d);
    path(G,  d, file, f);
    fprintf(file, "}\n");
    fclose(file);
    fclose(f);
    system("dot -Tpng output.dot -o output.png");
    system("catimg output.png");
    return;
}


void deleteALLVer(Graph* G){

    for(int i = 0; i < (G)->n; i++){
        deleteVerticals(&G, (G)->points[i]->name);
        i--;
    }
    return;
}
