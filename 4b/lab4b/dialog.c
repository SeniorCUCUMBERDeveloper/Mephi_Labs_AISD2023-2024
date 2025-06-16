#include "dialog.h"
#include "lib.h"
#include "time.h"

typedef struct data{
    int data;
    struct data* next;
}data;


typedef struct answ{
    int i;
    char* key;
    data* info;
}answ;


typedef struct node
{
	char* key[3];
	data** info;
	struct node* child[4];
	int leaf;
	int n;
}node;



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


int D_Add(node** tree)
{
        char* key;
        int info;
        printf("Input key\n");
        key = myreadline();
        getInt(&info, "Input info\n");
        insert(tree, key, info);
        return 1;
}


int D_Delete(node** tree)
{
        char* key;
        printf("Input key\n");
        key = myreadline();
        enum res flag = delete(tree, key);
        if(flag == -1){
                printf("Error, operation denied\n");
        }
        return 1;
}


int D_Find(node** tree)
{
        char* key;
        printf("Input key\n");
        key = myreadline();
        answ* mass = calloc(1, sizeof(answ));
        mass->key = NULL;
        search(*tree, key, &mass);
        if(mass->key == NULL){
        	free(key);
        	printf("Error, operation denied\n");
        	return -1;
        }
        data* ptr = mass->info;
        printf("key: %s\n", mass->key);
        printf("data: ");
        while(ptr != NULL){
        	printf("%d ", ptr->data);
        	ptr = ptr->next;
        }
        printf("\n");
        free(key);
        free(mass);
        return 1;
}

int D_Sort(node** tree){
        if(*tree == NULL){
        	printf("Operation denied :(\n");
        	return -1;
        }
        printf("travel left->right->root: ");
        travel(*tree);
        printf("\n");
        return 1;
}


int D_Show(node** tree){
		if(*tree == NULL){
			printf("Operation denied\n");
			return -1;
		}
        D_Dot(tree);
        system("catimg output.png");
        printf("\n");
        return 1;
}


int D_FindUniq(node** tree){
	if(*tree == NULL){
		return -1;
	}
	char* key;
	printf("Input key\n");
	key = myreadline();
	char* k = NULL;
	uniqsearch(*tree, key, &k);
	if(k == NULL){
		free(key);
		printf(":(\n");
		return 1;
	}
	printf("max key %s < %s\n",k , key);
	free(key);
	return 1;	
}


void to_dot(node* node, FILE *file) {
    fprintf(file, "node%p [label=\"", (void *)node);
    int i = 0;
    while(i < node->n){
        fprintf(file, "%s ", node->key[i]);
        i++;
    }
    fprintf(file, "\"];\n");
    i = 0;
    while(i <= node->n) {
        if (node->leaf == 0) {
            fprintf(file, "node%p -> node%p;\n", (void *)node, (void *)node->child[i]);
           	 to_dot(node->child[i], file);
        }
        i++;
    }
}



enum res indot(node* tree){
    if(tree == NULL){
        return Failed;
    }
    FILE* file = fopen("output.dot", "w");
    fprintf(file, "digraph b_tree {\n");
    fprintf(file, "node [shape=record];\n");
    to_dot(tree, file);
    fprintf(file, "}\n");
    fclose(file);
    system("dot -Tpng output.dot -o output.png");
    return Success;
}


int D_Dot(node** tree){
		indot(*tree);
        return 1;
}




int D_Dop(node** tree){
	Filereaddop();
	return 1;
}


int Fileread(node** tree){
		if(*tree != NULL){
                freenode(tree);
                *tree = NULL;
                return 0;
        }
        FILE* f = fopen("tree.txt", "r");
        char* key;
        int info;
        if(f != NULL){
                while(1){
                        if(feof(f)){
                                fclose(f);
                                return 1;
                        }
                        key = myread(f, key);
                        if(feof(f)){
                        	fclose(f);
                        	return 1;
                        }
                        fscanf(f, "%d", &info);
                        if(feof(f)){
                                fclose(f);
                                return 1;
                        }
                        fscanf(f, "%*[\n]");
                        insert(tree, key, info);
                }
        }
}

int insert(node** tree, char* key, int info){
	node* ptr = NULL;
	search_insert(*tree, &ptr, key);
	if(ptr == NULL){
		if(*tree == NULL){
			treecreate(tree);
		}
		InsertTree(tree, key, info);
	}else{
		int i = 0;
		for(i = 0; i < ptr->n && strcmp(key, ptr->key[i]) > 0; i++);
		data* new_info = malloc(sizeof(data));
		new_info->data = info;
		new_info->next = ptr->info[i];
		ptr->info[i] = new_info;
		free(key);
	}
	return 1;
}


int delete(node** tree, char* key){
	if(*tree == NULL){
		free(key);
		return -1;
	}
	node* ptr = NULL;
	search_insert(*tree, &ptr, key);
	if(ptr == NULL){
		free(key);
		return -1;
	}else{
		int i = 0;
		for(i = 0; i < ptr->n && strcmp(key, ptr->key[i]) > 0; i++);
		if(ptr->info[i]->next != NULL){
			data* ptr2 = ptr->info[i];
			data* ptr3 = ptr2;
			while(ptr3->next != NULL){
				ptr2 = ptr3;
				ptr3 = ptr3->next;
			}
			ptr2->next = NULL;
			free(ptr3);
		}else{
				node* cur = *tree;
				if (cur->leaf == 1)
				{
					int flag = delete_from_leaf_node(cur, key, cur->n - 1);
					if (flag == -1){
					    return -1;
					}
				}
				else {
					if (cur->n > 1) {
						deleteTree(&cur, key);
					}
					else {
					    handle_root_with_single_child(&cur, key, tree);
					}
				}
		}
	    free(key);
		return 1;
	}
}


char *generateRandomString(int len) {
    char *str = calloc((len + 1),sizeof(char));
	char set[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; 
    int i = 0;
    while(i < len){
    	str[i] = set[rand() % ((int)(sizeof(set) - 1))];
    	i++;
    }
    return str;
}


int Filereaddop(){
		node* t;
       	t = NULL;
        FILE* f = fopen("dop.txt", "r");
        char* key;
        int info = 1;
        if(f != NULL){
                while(1){
                		if(feof(f)){
                			fclose(f);
                			D_Show(&t);
                			D_Find(&t);
                			freenode(&t);
                			return 1;
                		}
                        key = myread(f, key);
                        fscanf(f, "%*[\n]");
                        char* str = strtok(key, " ");
                        while(str != NULL)
                        {
                        	char* cpy1 = calloc(strlen(str) + 1, sizeof(char));
                        	strcpy(cpy1, str);
                            insert(&t, cpy1, info);
                            str = strtok(NULL, " ");
                        }
                        free(key);
                        info++;
                }
        }
}


int D_Timing(node** )
{
        node* t = NULL;
        int n = 0,  con = 100000, i, m;
        char* key[10000];
        char* k;
        clock_t first, last;
        srand(time(NULL));
        while (n != 10)
        {
                i = 0;
                while(i < 10000)
                {
                        key[i] = generateRandomString(4);
                        i++;
                }
                i = 0;
                while(i < con)
                {
                        k = generateRandomString(4);
                        (insert(&t, k, 0));
                                i++;
                }
                m = 0;
                i = 0;
                first = clock();
                while(i < 10000)
                {	
                		int flag = -1;
                		search_for_insert(t, key[i], &flag);
                        if (flag != -1)
                        {
                                 m++;
                        }
                                i++;
                }
                last = clock();
                n++;
                printf("%d items was found\n", m);
                printf("test #%d, number of nodes = %d, time = %.0lf\n", n,n * con, 1000 * (double)(last - first)/CLOCKS_PER_SEC);
                i = 0;
                while(i < 10000){
                	free(key[i]);
                	i++;
                }
          
        }
                freenode(&t);
        		t = NULL;
        return 0;
}
