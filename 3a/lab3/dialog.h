#ifndef DIALOG_H
#define DIALOG_H


typedef struct Table Table;


const char* msgs[] = {"0.Quit", "1.Push", "2.Find", "3.Pop", "4.Print", "5.Import from .txt", "6.New table", "7.Remove elements"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
int D_Add(Table** table);
int D_Find(Table** table);
int D_Delete(Table** table);
int D_Show(Table** table);
int D_Import(Table** table);
int D_New(Table** table);
int D_Remove(Table** table);
int dialog(const char* msgs[], int N);


#endif
