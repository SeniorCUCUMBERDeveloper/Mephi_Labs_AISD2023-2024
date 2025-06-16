#ifndef DOP_H
#define DOP_H

typedef struct Node Node;

int intxt(Node* tree);
char* From_int_to_str(int x);
int Fileread_dop(Node** tree);
int push_dop(Node** tree, int key);


#endif
