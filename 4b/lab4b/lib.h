#ifndef LIB_H
#define LIB_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data data;
typedef struct answ answ;
typedef struct node node;
enum res {Success, Failed};



enum res treecreate(node** tree);
enum res InsertTree(node** tree, char* key, int info);
enum res insertnonfull(node* cur, char* k, int info);
enum res split(node* cur, int i, node** z);
enum res deleteTree(node** cur, char* k);
enum res handle_root_with_single_child(node** cur, char* key, node** root);
int delete_from_leaf_node(node* cur, char* key, int i);
node* Min(node* );
node* Max(node*);
int search_for_insert(node* tree,  char* key, int* flag);
int search(node* tree, char* key, answ** mass);
void travel(node* root);
enum res freeTree(node** root);
char* uniqsearch(node* tree, char* key, char** k);
node* search_insert(node* tree, node** ptr, char* key);
void freenode(node** t);


#endif
