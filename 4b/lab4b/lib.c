#include "lib.h"

typedef struct data{
    int data;
    struct data* next;
}data;


typedef struct answ{
    int i;
    char* key;
    data* info;
}answ;


typedef struct node{
	char* key[3];
	data** info;
	struct node* child[4];
	int leaf;
	int n;
}node;


void freenode(node** t){
	freeTree(t);
}


char* uniqsearch(node* tree, char* key, char** k){
    if(tree == NULL){
        return *k;
       }
    int i = 0;
    for(i = 0; i < tree->n && strcmp(key, tree->key[i]) > 0; i++){
        *k = tree->key[i];
    }
    if(i < tree->n && strcmp(key, tree->key[i]) == 0){
    	*k = key; 
        return key;
    }
    if(i < tree->n && strcmp(key, tree->key[i]) > 0){
        return *k;
    }
   if(tree->leaf == 0){
    uniqsearch(tree->child[i], key, k);
    }
    if(tree->leaf == 1){
    	return NULL;
    }
}


enum res freeTree(node** root) {
    if (root == NULL) {
        return Failed;
    }
    if ((*root)->leaf == 0) {
		int i = 0;
		while(i < (*root)->n + 1){
			freeTree(&((*root)->child[i]));
			i++;
		}
    }
	int i = 0;
    while(i < (*root)->n){
        data* ptr = (*root)->info[i];
        data* ptr2 = ptr;
        while(ptr2 != NULL){
                ptr2 = ptr2->next;
                free(ptr);
                ptr = ptr2;
        }
        free((*root)->key[i]);
		i++;
    }
    free((*root)->info);
    free(*root);
	return Success;
}


void travel(node* tree) {
    if (tree == NULL) {
        return;
    }
	int i = 0;
	while(i < tree->n)
	{
		if(tree->leaf == 0){
        travel(tree->child[i]);
        }
        printf("%s ", tree->key[i]); 
		i++;
    }
    if(tree->leaf == 0){
		travel(tree->child[i]);
	}
}


enum res treecreate(node** tree)
{
	node* x = malloc(sizeof(node));
	if(x == NULL){
		return Failed;
	}
	x->info = calloc(3, sizeof(data*));
	for(int i = 0; i < 4; i++){
	    
	    x->child[i] = NULL;
	}
	x->leaf = 1;
	x->n = 0;
	(*tree) = x;
	return Success;
}



node* initROOT(node** tree, node** root){
	node* new_root = malloc(sizeof(node));
	new_root->info = calloc(3, sizeof(data*));
	(*tree) = new_root;
	new_root->leaf = 0;
	new_root->n = 0;
	new_root->child[0] = *root;
	new_root->child[1] = NULL;
	new_root->child[2] = NULL;
	new_root->child[3] = NULL;
	return new_root;
}


enum res InsertTree(node** tree, char* key, int info)
{
	node* root = *tree;
	if (root != NULL && root->n == 3)
	{
		node* new_root = initROOT(tree, &root); 
		node* right;
		split(new_root, 0, &right);
		insertnonfull(new_root, key, info);
		return Success;
	}
	else
	{
		insertnonfull(root, key, info);
		return Success;
	}
}


int correct_for_leaf(node** tree, char* key, int i){
	for(;i >= 0 && strcmp(key, (*tree)->key[i]) < 0; i--){
		(*tree)->key[i + 1] = (*tree)->key[i];
		(*tree)->info[i + 1] = (*tree)->info[i];
	}
	return i;
}


enum res insert_info_for_leaf(node** tree, int info, int i){
	data* ptr = malloc(sizeof(data));
	ptr->data = info;
	ptr->next = NULL;
	(*tree)->info[i + 1] = ptr;
	return Success;
}


enum res Insert_to_leaf(node* tree, char* key, int info, int i){
        i--;
		i = correct_for_leaf(&tree, key, i);
		tree->key[i + 1] = key;
		insert_info_for_leaf(&tree, info, i);
		tree->n = tree->n + 1;
		return Success;
}


int countIndexkey(node** x, char* k, int i){
	for(;i >= 1 && strcmp(k, (*x)->key[i - 1]) < 0; i--);
	return i;
}


int search_for_insert(node* tree, char* key, int* flag){
    if(tree == NULL){
        return -1;
    }
    int i = 0;
    for(i = 0; i < tree->n && strcmp(key, tree->key[i]) > 0; i++);
    if(i < tree->n && strcmp(key, tree->key[i]) == 0){
    	*flag = i;
        return i;
    }
    if(tree->leaf == 0)
    {
    search_for_insert(tree->child[i], key, flag);
    }
    if(tree->leaf == 1){
    	return -1;
    }
}


int Insert_To_full_child(node* tree, char* key, int i){
    node* right;
	split(tree, i, &right);
	if (strcmp(key, tree->key[i]) > 0) {
		i++;
	}
	return i;
}


enum res Insert_to_NoTleaf(node* tree, char* key, int info, int i){
		i = countIndexkey(&tree, key, i);
		if ((tree->child[i])->n == 3)
		{
			i = Insert_To_full_child(tree, key, i);
		}
		insertnonfull(tree->child[i], key, info);
		return Success;
}


enum res insertnonfull(node* tree, char* key, int info)
{
	if (tree->leaf == 1)
	{
		return Insert_to_leaf(tree, key, info, tree->n);
	}
	else {
	    return Insert_to_NoTleaf(tree, key, info, tree->n);	
	}
}


enum res splitLeaf(node** right, node* splited){
    (*right)->child[0] = splited->child[2];
	(*right)->child[1] = splited->child[3];
	return Success;

}


enum res correctChild(node** parent, int i){
	int j = (*parent)->n;
	while(j > i){
	    (*parent)->child[j + 1] = (*parent)->child[j];
	    j--;
	}
	return Success;
}


enum res correctKeys(node** parent, node** splited, int i){
    int j = (*parent)->n - 1;
    while(j > i - 1){
        (*parent)->key[j + 1] = (*parent)->key[j];
		(*parent)->info[j + 1] = (*parent)->info[j];
		j--;
    }
	(*parent)->key[i] = (*splited)->key[1];
	(*parent)->info[i] = (*splited)->info[1];
	return Success;
}


enum res createRightptr(node** right, node** splited, node** parent, int i){
    *splited = (*parent)->child[i];
	(*right)->leaf = (*splited)->leaf;
	(*right)->n = 1;
	(*right)->key[0] = (*splited)->key[2];
	(*right)->info[0] = (*splited)->info[2];
	return Success;
}


enum res split(node* parent, int i, node** right)
{
	*right = malloc(sizeof(node));
	(*right)->info = calloc(3, sizeof(data*));
	node* splited;
	createRightptr(right, &splited, &parent, i);
	if (splited->leaf == 0)
	{
	    splitLeaf(right, splited);
	}
	splited->n = 1;
	correctChild(&parent, i);
	parent->child[i + 1] = *right;
	correctKeys(&parent, &splited, i);
	parent->n = parent->n + 1;
	return Success;
}



enum res correct_data_for_leaf(node** cur, int i){
	int j = i + 1;
	while(j < (*cur)->n)
	{
		(*cur)->key[j - 1] = (*cur)->key[j];
		(*cur)->info[j - 1] = (*cur)->info[j];
		j++;
	}
	return Success;
}


int delete_from_leaf_node(node* cur, char* key, int i){
	for(; i >= 0 && cur->key[i] != NULL && strcmp(cur->key[i], key) > 0; i--);
	if (i >= 0 && cur->key[i] != NULL && strcmp(cur->key[i], key)  == 0){
		free(cur->key[i]);
		free(cur->info[i]);
		correct_data_for_leaf(&cur, i);
		cur->n--;
		return 1;
	}
	return -1;
}


enum res copy_keys_from_parent(node** cur, node** left, node** right){
    (*left)->key[1] = (*cur)->key[0];
	(*left)->info[1] = (*cur)->info[0];
	(*left)->key[2] = (*right)->key[0];
	(*left)->info[2] = (*right)->info[0];
	return Success;
}


enum res copy_children_from_parent(node** left, node** right){
    if ((*left)->leaf == 0) {
    		(*left)->child[2] = (*right)->child[0];
    		(*left)->child[3] = (*right)->child[1];
		}
	return Success;
}


enum res merge(node** cur, node** left, node** right, node** root, char* key){
	copy_keys_from_parent(cur, left, right);
	copy_children_from_parent(left, right);
	(*left)->n = 3;
	free((*right)->info);
	free(*right);
	(*root) = (*left);
	free((*cur)->info);
	free(*cur);
	deleteTree(left, key);
	return Success;
}


enum res handle_root_with_single_child(node** cur, char* key, node** root){
	node* l_child = (*cur)->child[0];
	node* r_child = (*cur)->child[1];
	if (l_child->n == 1 && r_child->n == 1) {
        merge(cur, &l_child, &r_child, root, key);	
	}
	else {
		deleteTree(cur, key);
	}
	return Success;
}


int find_index(node** cur, char* key){
    int i = (*cur)->n;
	for(;i > 0 && (*cur)->key[i - 1] != NULL && strcmp((*cur)->key[i - 1], key)>= 0; i--);
	return i;
}


enum res delete_from_leaf(node** cur, int i)
{
    free((*cur)->key[i]);
    free((*cur)->info[i]);
	int j = i;
	while(j < (*cur)->n - 1){
		(*cur)->key[j] = (*cur)->key[j + 1];
		(*cur)->info[j] = (*cur)->info[j + 1];
		j++;
	}
	(*cur)->n--;
	return Success;
}


enum res merge_children(node** cur, node** l_child, node** r_child, int i) {
  (*l_child)->key[1] = (*cur)->key[i];//k
  (*l_child)->info[1] = (*cur)->info[i];
  (*l_child)->key[2] = (*r_child)->key[0];
  (*l_child)->info[2] = (*r_child)->info[0];
  (*l_child)->child[2] = (*r_child)->child[0];
  (*l_child)->child[3] = (*r_child)->child[1];
  (*l_child)->n = 3;
  return Success;
}

enum res delete_key(node** cur, node** l_child, node** r_child, char* key, int i) {
  int j = i;
  while(j < (*cur)->n - 1){
    (*cur)->key[j] = (*cur)->key[j + 1];
    (*cur)->info[j] = (*cur)->info[j + 1];
    j++;
  }
  j = i + 1;
  while(j < (*cur)->n){
    (*cur)->child[j] = (*cur)->child[j + 1];
    j++;
  }
  (*cur)->n--;
  free((*r_child)->info);
  free(*r_child);
  deleteTree(&*l_child, key);
  return Success;
}


enum res handle_case_1(node** cur, node** l_child, int i) {
  node* ptr = Max(*l_child);
  char* key = (*cur)->key[i];
  data* info = (*cur)->info[i];
  (*cur)->key[i] = ptr->key[ptr->n - 1];
  (*cur)->info[i] = ptr->info[ptr->n - 1];
  ptr->key[ptr->n - 1] = key;
  ptr->info[ptr->n - 1] = info;
  deleteTree(&*l_child, ptr->key[ptr->n - 1]);
  return Success;
}


enum res handle_case_2(node** cur, node** r_child, int i) {
  node* ptr = Min(*r_child);
  char* key = (*cur)->key[i];
  data* info = (*cur)->info[i];
  (*cur)->key[i] = ptr->key[0];
  (*cur)->info[i] = ptr->info[0];
  ptr->key[0] = key;
  ptr->info[0] = info;
  deleteTree(&*r_child, ptr->key[0]);
  return Success;
}


enum res handle_case_3(node** cur, node** l_child, node** r_child, int i, char* key) {
  merge_children(cur, l_child, r_child, i);
  delete_key(cur, l_child, r_child, key, i);
  return Success;
}


enum res handle_internal_node(node** cur, int i, char* key) {
	node* l_child = (*cur)->child[i];
	node* r_child = (*cur)->child[i + 1];
	if (l_child->n > 1) {
		handle_case_1(cur, &l_child, i);
	}
	else if (r_child->n > 1) {
		handle_case_2(cur, &r_child, i);
	}
	else {
		handle_case_3(cur, &l_child, &r_child, i, key);
	}
	return Success;
}


enum res redistribute_right(node** cur, node** cur_next, int i){
	node* r_child = (*cur)->child[i + 1];
	r_child->key[2] = r_child->key[0]; r_child->info[2] = r_child->info[0];
	r_child->key[0] = (*cur_next)->key[0]; r_child->info[0] = (*cur_next)->info[0];
	if (r_child->leaf == 0) {
		r_child->child[2] = r_child->child[0]; r_child->child[0] = (*cur_next)->child[0];
		r_child->child[3] = r_child->child[1]; r_child->child[1] = (*cur_next)->child[1];
	}
	r_child->key[1] = (*cur)->key[i]; r_child->info[1] = (*cur)->info[i];
	r_child->n = 3;
	int j = 0;
	while(j < (*cur)->n - 1){
		(*cur)->key[j] = (*cur)->key[j + 1]; (*cur)->info[j] = (*cur)->info[j + 1];
		j++;
	}
	j = 0;
	while(j < (*cur)->n){
		(*cur)->child[j] = (*cur)->child[j + 1];
		j++;
	}
	free((*cur_next)->info); free(*cur_next);
	*cur_next = r_child; (*cur)->n--;
	return Success;

}


enum res redistribute_left(node** cur, node** cur_next, int i){
	node* l_child = (*cur)->child[i - 1];
	l_child->key[1] = (*cur)->key[i - 1]; l_child->info[1] = (*cur)->info[i - 1];
	l_child->key[2] = (*cur_next)->key[0]; l_child->info[2] = (*cur_next)->info[0];
	if (l_child->leaf == 0) {
		l_child->child[2] = (*cur_next)->child[0]; l_child->child[3] = (*cur_next)->child[1];
	}
	l_child->n = 3;
	int j = i - 1;
	while(j < (*cur)->n - 1){
		(*cur)->key[j] = (*cur)->key[j + 1]; (*cur)->info[j] = (*cur)->info[j + 1];
		j++;
	}
	j = i;
	while(j < (*cur)->n){
		(*cur)->child[j] = (*cur)->child[j + 1];
		j++;
	}
	free((*cur_next)->info); free(*cur_next);
	*cur_next = l_child; (*cur)->n--;
	return Success;
}


enum res rotate_left_case(node** cur, node** cur_next, int i){
	node* l_child = (*cur)->child[i - 1];
	(*cur_next)->key[1] = (*cur_next)->key[0]; (*cur_next)->info[1] = (*cur_next)->info[0];
	if ((*cur_next)->leaf == 0)
	{
		(*cur_next)->child[2] = (*cur_next)->child[1]; (*cur_next)->child[1] = (*cur_next)->child[0];
	}
	(*cur_next)->key[0] = (*cur)->key[i - 1]; (*cur_next)->info[0] = (*cur)->info[i - 1];
	(*cur_next)->child[0] = l_child->child[l_child->n];
	(*cur_next)->n++;
	(*cur)->key[i - 1] = l_child->key[l_child->n - 1]; (*cur)->info[i - 1] = l_child->info[l_child->n - 1];
	l_child->n--;
	return Success;
}


enum res rotate_right_case(node** cur, node** cur_next, int i){
	node* r_child = (*cur)->child[i + 1];
	(*cur_next)->key[1] = (*cur)->key[i]; (*cur_next)->info[1] = (*cur)->info[i];
	(*cur_next)->child[2] = r_child->child[0];
	(*cur_next)->n++;
	(*cur)->key[i] = r_child->key[0]; (*cur)->info[i] = r_child->info[0];
	int j = 0;
	while(j < r_child->n - 1){
		r_child->key[j] = r_child->key[j + 1]; r_child->info[j] = r_child->info[j + 1];
		j++;
	}
	j = 0;
	while(j < r_child->n){
		r_child->child[j] = r_child->child[j + 1];
		j++;	
	}
	r_child->n--;
	return Success;
}


enum res handle_nonexistent_key(node* cur, int i, char* key){
    node* cur_next = cur->child[i];
		if(cur_next == NULL){
		    return Failed;
		}
		if (cur_next->n > 1)
		{
			deleteTree(&cur_next, key);
		}
		else
		{
			if (i != 0 && (cur->child[i - 1])->n > 1)
			{
				rotate_left_case(&cur, &cur_next, i);
				deleteTree(&cur_next, key);
			}
			else if (i != cur->n && (cur->child[i + 1])->n > 1)
			{
				rotate_right_case(&cur, &cur_next, i);
				deleteTree(&cur_next, key);
				
			}
			else {
				if (i == 0) {
					redistribute_right(&cur, &cur_next, i);
					deleteTree(&cur_next, key);
				}
				else {
					redistribute_left(&cur, &cur_next, i);
					deleteTree(&cur_next, key);
				}
			}
		}
		return Success;
}


enum res deleteTree(node** x, char* k) {
	int i = find_index(x, k);
	if (i < (*x)->n && (*x)->key[i] != NULL && strcmp((*x)->key[i], k) == 0) {
		if ((*x)->leaf == 1) {
		    delete_from_leaf(x, i);
		}
		else {
		    handle_internal_node(x, i, k);
		}
	}
	
	else
	{
	     handle_nonexistent_key(*x, i, k);
	}
	return Success;
}


node* Max(node* x) {
	while (x->leaf == 0) {
		x = x->child[x->n];
	}
	return x;
}


node* Min(node* x) {
	while (x->leaf == 0) {
		x = x->child[0];
	}
	return x;
}


int search(node* tree, char* key, answ** mass){
    if(tree == NULL){
        return 0;
    }
    int i = 0;
    for(i = 0; i < tree->n && strcmp(key, tree->key[i]) >= 0; i++){
        if(strcmp(key, tree->key[i]) == 0)
        {
            (*mass)->key = tree->key[i];
            (*mass)->info = tree->info[i];
        }
    }
    if((*mass)->key != NULL){
        return 1;
    }
    if(tree->leaf == 0)
    {
    search(tree->child[i], key, mass);
    }
    if(tree->leaf == 1){
    	return 0;
    }
}


node* search_insert(node* tree, node** ptr, char* key){
    if(tree == NULL){
        return NULL;
    }
    int i = 0;
    for(i = 0;  i < tree->n && strcmp(key, tree->key[i]) > 0; i++);
    if(i < tree->n && strcmp(key, tree->key[i]) == 0){
    	(*ptr) = tree;
        return tree;
    }
    if(tree->leaf == 0)
    {
    search_insert(tree->child[i], ptr, key);
    }
    if(tree->leaf == 1){
    	return NULL;
    }
}



