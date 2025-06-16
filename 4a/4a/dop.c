#include "lib.h"
#include "queue.h"
#include "dop.h"


typedef struct Node{
    int key;
    char* info;
    struct Node *left, *right;
}Node;


typedef struct Info{
   Node* data;
   struct Info* next;
}Info;


typedef struct Stack{
    Info* head;
}Stack;


int push_dop(Node** tree, int key){
        if(*tree == NULL){
        	char* info = calloc(2, sizeof(char));
        	info[0] = '1';
            *tree = createNode(key, info);
            return 0;
        }
        Node* current = (*tree);
        Node* parante = NULL;
        while(current != NULL){
                if(key == current->key){
                    int x = atoi(current->info);
                    free(current->info);
                    x = x + 1;
                    char* new_info = From_int_to_str(x);
                    current->info = new_info;
                    return 0;
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
        	char* info = calloc(2, sizeof(char));
        	info[0] = '1';
            parante->left = createNode(key, info);
            return 0;
        }
        char* info = calloc(2, sizeof(char));
        info[0] = '1';
        parante->right = createNode(key, info);
        return 0;
}


int Fileread_dop(Node** tree){
	if(tree != NULL){
		deleted(tree);
	}
	FILE* f = fopen("dop.txt", "r");
	int key;
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
			push_dop(tree, key);
		}
	}
}


char* From_int_to_str(int x){
    int a = x;
    int k = 0;
    while(a != 0){
        a = a / 10;
        k++;
    }
    k++;
    char* str = malloc(sizeof(char) * k);
    snprintf(str, k, "%d", x);
    return str;
}


int intxt(Node* tree){
    if(tree == NULL){
        return 1;
    }
    FILE* file = fopen("dopresult.txt", "w");
    Node* ptr = tree;
    Stack* stack = malloc(sizeof(Stack));
    stack->head = NULL;
    while(ptr != NULL || stack->head != NULL){
        while(ptr != NULL){
            add(stack, ptr);
            ptr = ptr->right;
        }
        ptr = del(stack);
        fprintf(file, "%d - %s\n", ptr->key, ptr->info);
        ptr = ptr->left;
    }
    fclose(file);
    free(stack);
    return 0;
}
