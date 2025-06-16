#include "dialog.h"
#include "lib.h"


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


char *myreadline()
{
    scanf("%*[\n]");
    int storage = 82;
    char* line1 = (char *) calloc(storage+1, sizeof(char));
    int len = 82;
    while(scanf("%82[^\n]", &line1[(len - storage)]) != 0) 
    {
        
        len += storage;
        line1 = (char *) realloc(line1, ((len) + 1) * sizeof(char));
    }
    line1[strlen(line1)] = '\0';
    line1 = (char *) realloc(line1, (strlen(line1) + 3) * sizeof(char));
    return line1;
}


int getInt(int* num, const char* pr)
{
    int res = 0;
    int e;
    printf("%s ", pr);
    do{
        res = scanf("%d.%d", num, &e);
        if (res < 0 || res == EOF )
        {
                printf("EOF\n");
            return 0;
        }
        if ((res == 0 || res == 2))
        {
            printf("Incorrect symbol\n");
            printf("Please, try again = ");
            scanf("%*[^\n]");
        }
    }while(res != 1);
    return 1;
}


int dialog(const char* msgs[], int N){
    char* errmsg = "";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for(i = 0; i < N; ++i){
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");
        n = getInt(&rc, ""); 
        if(n != 1 || rc > 17){
            rc = -1;
        }
    } while(rc < 0);
    return rc;
}


int D_Primer(Graph* G){
	char* a = calloc(2, sizeof(char));
	a[0] = 'a';
	char* b = calloc(2, sizeof(char));
	b[0] = 'b';
	char* c = calloc(2, sizeof(char));
	c[0] = 'c';
	char* d = calloc(2, sizeof(char));
	d[0] = 'd';
	char* e = calloc(2, sizeof(char));
	e[0] = 'e';
	addVertex(G, a);
    addVertex(G, b);
    addVertex(G, c);
    addVertex(G, d);
    addVertex(G, e);
    addEdges(G, a, b, 6);
    addEdges(G, a, e, 7);
    addEdges(G, b, c, 5);
    addEdges(G, b, d, -4);
    addEdges(G, b, e, 8);
    addEdges(G, c, b, -2);
    addEdges(G, d, a, 2);
    addEdges(G, d, c, 7);
    addEdges(G, e, c, -3);
    addEdges(G, e, d, 9);
    return 1;
}

int D_Add_V(Graph* G){
	printf("Input name\n");
	char* name = myreadline();
	int i = addVertex(G, name);
	if(i == -1){
		free(name);
	}
	return 1;
}


int D_Add_E(Graph* G){
	if(G->points == NULL){
		return -1;
	}
	printf("Input from char\n");
	char* from = myreadline();
	printf("Input to char\n");
	char* to = myreadline();
	int weight;
	printf("Input weight\n");
	scanf("%d", &weight);
	addEdges(G, from, to, weight);
	free(from);
	free(to);
	return 1;
}


int D_Show(Graph* G){
	printGraph(G);
	return 1;
}


int D_Delete_E(Graph* G){
	printf("Input from char\n");
	char* from = myreadline();
	printf("Input to char\n");
	char* to = myreadline();
	deleteEdge(G, from, to);
	free(from);
	free(to);
	return 1;
}


int D_Delete_V(Graph* G){
	printf("Input from char\n");
	char* from = myreadline();
	deleteVerticals(&G, from);
	free(from);
}


int D_Matrix(Graph* G){
	int** matrix = matr(G);
	printMatrix(matrix, G->n);
	deleteMatr(matrix, G->n);
	return 1;
}


int D_Path(Graph* G){
	printf("Input index\n");
	int i;
	scanf("%d", &i);
	
	path(G, i, NULL, NULL);
	return 1;
}


int D_DFS(Graph* G){
	int* mass = calloc(G->n, sizeof(int));
	int i;
	printf("Input index\n");
	scanf("%d", &i);
	DFS(G->points[i], mass);
	printf("\n");
	free(mass);
	return 1;
}


int D_CC(Graph* G){
	findConnectedComponents(G);
	return 1;
}


int D_Correct(Graph* G){
	printf("Input name\n");
	char* name = myreadline();
	printf("Input new name\n");
	char* new = myreadline();
	int i = New_name(G, name, new);
	free(name);
	if(i == -1){
		free(new);
	}
	return 1;
}


int D_Dot(Graph* G){
	if(G->points == NULL){
		return -1;
	}
	indot(G);
	system("dot -Tpng output.dot -o output.png");
	system("catimg output.png");
	return 1;
}


int D_Dop1(Graph* G){
	if(G->points == NULL){
		return -1;
	}
	dop1(G);
	return 1;
}


int D_Dop2(Graph* G){
	if(G->points == NULL){
		return -1;
	}
	dop2(G);
	return 1;
}


int D_Dop3(Graph* G){
	if(G->points == NULL){
		return -1;
	}
	dop3(G);
	return 1;
}


char* myread(FILE* f, char* line1)
{
    int storage = 82;
    line1 = (char *) calloc(storage+1, sizeof(char));
    int len = 82;
    while(fscanf(f, "%82[^\n]", &line1[(len - storage)]) != 0) 
    {
        
        len += storage;
        line1 = (char *) realloc(line1, ((len) + 1) * sizeof(char));
    }
    line1[strlen(line1)] = '\0';
    line1 = (char *) realloc(line1, (strlen(line1) + 3) * sizeof(char));
    return line1;
}


int D_Gen(Graph* G){
	if(G->points != NULL){
		deleteALLVer(G);
	}
	FILE* f = fopen("graph.txt", "r");
	int key;
	char* name1;
	char* name2;
	int w;
	if(f != NULL){
		for(int i = 0; i < 250; i++){
			char* name = myread(f, name);
			fscanf(f, "%*[\n]");
			int i = addVertex(G, name);
			if(i == -1){
				free(name);
			}
		}
		while(1){
			if(feof(f)){
				fclose(f);
				return 1;
			}
			fscanf(f, "%d", &key);
			if(feof(f)){
				fclose(f);
				return 1;
			}
			fscanf(f, "%*[\n]");
			name1 = myread(f, name1);
			fscanf(f, "%*[\n]");
			name2 = myread(f, name2);
			fscanf(f, "%d", &w);
			addEdges(G, name1, name2, w);
			free(name1);
			free(name2);
		}
	}
}
