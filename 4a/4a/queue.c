#include "queue.h"


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


void add(Stack* stack, Node* x){
    Info* ptr = malloc(sizeof(Info));
    ptr->next = NULL;
    ptr->data = x;
    if(stack->head == NULL){
        stack->head = ptr;
    }else{
        ptr->next = stack->head;
        stack->head = ptr;
    }
    return;
}


Node* del(Stack* stack){
    if(stack->head == NULL){
        return NULL;
    }
    Info* info = stack->head;
    stack->head = stack->head->next;
    Node* ptr = info->data;
    info->next = NULL;
    free(info);
    return ptr;
}
