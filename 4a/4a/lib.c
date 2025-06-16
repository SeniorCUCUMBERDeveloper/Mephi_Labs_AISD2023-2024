#include "lib.h"
#include "queue.h"


typedef struct Node{
    int key;
    char* info;
    struct Node *left, *right;
}Node;


typedef struct answ{
    Node** ptr;
    int i;
    int h;
}answ;


typedef struct Info{
   Node* data;
   struct Info* next;
}Info;


typedef struct Stack{
    Info* head;
}Stack;


Node* createNode(int key, char* info)
{
    Node* ptr = malloc(sizeof(Node));
    ptr->key = key;
    ptr->info = info;
    ptr->left = NULL;
    ptr->right = NULL;
    return ptr;
}


Node* MiNode(Node* tree){
    while(tree->left != NULL){
        tree = tree->left;
    }
    return tree;
}


char* push(Node** tree, int key, char* info){
        if(*tree == NULL){
            *tree = createNode(key, info);
            return NULL;
        }
        Node* current = (*tree);
        Node* parante = NULL;
        while(current != NULL){
                if(key == current->key){
                    char* copy = current->info;
                    current->info = info;
                    return copy;
                }
                parante = current;
                if(key > current->key){
                        current = current->right;
                    }
                else if((key < current->key)){
                        current = current->left;
                    }
            }
        if(key < parante->key){
            parante->left = createNode(key, info);
            return NULL;
        }
        parante->right = createNode(key, info);
        return NULL;
}


Node* searchPrev(Node* current, int key){
    Node* parante = NULL;
    while(current != NULL && current->key != key){
            parante = current;
            if(key > current->key){
                    current = current->right;
                }
            else if((key < current->key)){
                    current = current->left;
                }
        }
        return parante;
}


void printTree(Node *tree, int depth)
{
        if (tree != NULL){
            printTree(tree->right, depth + 1);
            for(int i = depth; i > 0; i--)
            {
                printf("     ");
            }
            printf("%d\n", tree->key);
        printTree(tree->left, depth + 1);
    }
}


int pop(Node** tree, int key){
    if(*tree == NULL){
        return 1;
    }
    Node* current = *tree;
    Node* parante = NULL;
    while(current != NULL && current->key != key)
    {
        if(key < current->key){
            parante = current;
            current = current->left;
        }else if(key > current->key){
            parante = current;
            current = current->right;
        }
    }
    if(current == NULL){
        return -1;
    }
    if(key == current->key){
        if(current->left == NULL && current->right == NULL){
        	if(parante != NULL)
        	{
	            if(parante->left == current){
	                parante->left = NULL;
	            }else{
	                parante->right = NULL;
	            }
	        }else{
	        	*tree = NULL;
	        }
            free(current->info);
            free(current);
            current = NULL;
            return 0;
        }
        else if(current->left == NULL){
            Node* del = current;
            if(parante != NULL)
            {
                if(parante->right == current){
                   parante->right = current->right; 
                }else{
                    parante->left = current->right; 
                }
            }else{
                *tree = current->right;
            }
            free(del->info);
            free(del);
            return 0;
        }else if(current->right == NULL)
        {
            Node* del = current;
            if(parante != NULL){
                if(parante->right == current){
                   parante->right = current->left; 
                }else{
                    parante->left = current->left; 
                }
            }else{
                *tree = current->left;
            }
            free(del->info);
            free(del);
            return 0;
        }
        Node* ptr = current;
        Node* min = MiNode(current->right);
        Node* prev = searchPrev(current, min->key);
        if(prev != NULL && prev->right != NULL &&  prev->right->key == min->key){
            prev->right = prev->right->right;
        }
        if(prev != NULL && prev->left != NULL && prev->left->key == min->key){
            prev->left = prev->left->left;
        }
        if(parante != NULL)
        {
            if(parante->left == current){
                parante->left = min;
            }
            if(parante->right == current){
                parante->right = min;
            }
        }else{
            *tree = min;
        }
        min->left = ptr->left;
        min->right = ptr->right;
        free(ptr->info);
        free(ptr);
        return 0;
    }
}


char* search(Node* tree, int key){
    if(tree == NULL){
        return NULL;
    }
    while(tree != NULL){
        if(key == tree->key){
            return tree->info;
        }
        if(key < tree->key){
            tree = tree->left;
        }else{
            tree = tree->right;
        }
    }
    return NULL;
}


answ* uniqsearch(Node* tree, int key, answ* arr){
    if(tree == NULL){
        return arr;
    }
    while(tree != NULL){
        if(tree->key == key){
            arr->ptr[0] = tree;
            return arr;
        }
        if(abs(tree->key - key) == arr->h){
            arr->ptr[arr->i] = tree;
        }
        if(abs(tree->key - key) < arr->h){
            if(arr->ptr[0] != NULL || arr->ptr[1] != NULL){
                arr->ptr[0] = NULL;
                arr->ptr[1] = NULL;
                arr->i = 0;
            }
            arr->ptr[(arr->i)++] = tree; 
            arr->h = abs(tree->key - key);
        }
        if(key < tree->key){
            tree = tree->left;
        }else{
            tree = tree->right;
        }
    }
    return arr;
}


int indot(Node* tree){
    if(tree == NULL){
        return 1;
    }
    FILE* file = fopen("output.dot", "w");
    fprintf(file, "digraph G {\n");
    Node* ptr = tree;
    Stack* stack = malloc(sizeof(Stack));
    stack->head = NULL;
    while(ptr != NULL || stack->head != NULL){
        while(ptr != NULL){
            add(stack, ptr);
            ptr = ptr->left;
        }
        ptr = del(stack);
        Node* prev = searchPrev(tree, ptr->key);
        if(prev != NULL)
        {
            fprintf(file, "\t%d->", prev->key);
            fprintf(file, "%d;\n", ptr->key);
        }
        ptr = ptr->right;
    }
    free(stack);
    fprintf(file, "}\n");
    fclose(file);
    return 0;
}


int deleted(Node** t){
	Node* tree = (*t);
    if(tree == NULL){
        return 1;
    }
    Node* ptr = tree;
    Stack* stack = malloc(sizeof(Stack));
    stack->head = NULL;
    while(ptr != NULL || stack->head != NULL){
        while(ptr != NULL){
            add(stack, ptr);
            ptr = ptr->right;
        }
        ptr = del(stack);
        Node* delete = ptr;
        ptr = ptr->left;
        if(delete->info != NULL){
        	free(delete->info);
        }
        free(delete);
    }
    printf("\n");
    free(stack);
    return 0;
}


int searchFORtiming(Node* tree, int key){
    if(tree == NULL){
        return 0;
    }
    while(tree != NULL){
        if(key == tree->key){
            return 1;
        }
        if(key < tree->key){
            tree = tree->left;
        }else{
            tree = tree->right;
        }
    }
    return 0;
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


int Fileread(Node** tree){
        if(tree != NULL){
                deleted(tree);
                *tree = NULL;
        }
        FILE* f = fopen("tree.txt", "r");
        int key;
        char* info;
        if(f != NULL){
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
                        info = myread(f, info);
                        push(tree, key, info);
                }
        }
        
}


int sorted_b(Node* tree){
	if(tree == NULL){
		return 0;
	}
	sorted_b(tree->left);
	sorted_b(tree->right);
	printf("%d ", tree->key);
}
