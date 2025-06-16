#include "dialog.h"
#include "lib.h"
#include "dop.h"
#include <time.h>

typedef struct answ{
    Node** ptr;
    int i;
    int h;
}answ;


typedef struct Node{
    int key;
    char* info;
    struct Node *left, *right;
}Node;


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
        if(n != 1 || rc > 10){
            rc = -1;
        }
    } while(rc < 0);
    return rc;
}


int D_Add(Node** tree)
{
        int key;
        getInt(&key, "Imput key\n");
        printf("Imput info\n");
        char* info = myreadline();
        char* cpy = push(tree, key, info);
        if(cpy != NULL)
        {
            printf("copy info: %s\n", cpy);
            free(cpy);
        }
        return 1;
}


int D_Delete(Node** tree)
{
       	int key;
       	getInt(&key, "Imput key\n");
       	int flag = pop(tree, key);
        if(flag != 0){
                printf("Error, operation denied\n");
        }
        return 1;
}


int D_Find(Node** tree)
{
        int key;
        getInt(&key, "Input key\n");
        char* str = search(*tree, key);
        if(str != NULL)
        {
                printf("%s\n", str);
        }
        return 1;
}


int D_Sort(Node** tree){
	int key;
	getInt(&key, "Input key\n");
	int flag = sorted_b(*tree);
	if(flag == 1){
		printf("Error, operation denied\n");
	}
	return 1;
}


int D_Show(Node** tree){
	printTree(*tree, 0);
	return 1;
}


int D_FindUniq(Node** tree){
	int key;
	getInt(&key, "Input key\n");
	answ* arr = malloc(sizeof(answ));
	arr->ptr = malloc(sizeof(Node*) * 2);
	arr->h = 1334;
	arr->i = 0;
	arr->ptr[0] = NULL;
	arr->ptr[1] = NULL;
	arr = uniqsearch(*tree, key, arr);
	if(arr->ptr[0] != NULL){
		printf("%d ", arr->ptr[0]->key);
	}
	if(arr->ptr[1] != NULL){
		printf("%d\n", arr->ptr[1]->key);
	}
	free(arr->ptr);
	free(arr);
}


int D_Dot(Node** tree){
	indot(*tree);
	return 1;
}


int D_Timing(Node **)
{
	Node *root = NULL;
	int n = 0, key[10000], k, con = 1000000000, i, m;
	clock_t first, last;
	srand(time(NULL));
	while (n != 10)
	{
		i = 0;
		while(i < 10000)
		{
			key[i] = rand() * 11;
			i++;
		}
		i = 0;
		while(i < con)
		{
			k = rand() * 11;
			if (push(&root, k, NULL) == NULL){
				i++;
			}
		}
		m = 0;
		i = 0;
		first = clock();
		while(i < 10000)
		{
			if (searchFORtiming(root, key[i]) == 1)
			{
				 m++;
			}
				i++;
		}
		last = clock();
		n++;
		printf("%d items was found\n", m);
		printf("test #%d, number of nodes = %d, time = %.0lf\n", n,n * con, 1000 * (double)(last - first)/CLOCKS_PER_SEC);
	}
	deleted(&root);
	return 1;
}


int D_Dop(Node** tree){
	Node* root = NULL;
	Fileread_dop(&root);
	intxt(root);
	deleted(&root);
	return 1;
}
