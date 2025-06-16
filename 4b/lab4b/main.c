#include "lib.h"
#include "dialog.h"


int main(){
    node* T = NULL;
    int rc;
    const char* msgs[] = {"0.Quit", "1.Push", "2.Find", "3.Pop", "4.Print", "5.Obxod?????", "6.Uniq find", "7. .dot", "8.Timing", "9.File", "10.Dop"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*fptr[])(node**) = {NULL, D_Add, D_Find, D_Delete, D_Show, D_Sort, D_FindUniq, D_Dot, D_Timing, Fileread, D_Dop}; 
    while(rc = dialog(msgs, NMsgs)){
        if (fptr[rc](&T) == 0){
            break;
        }
    }
    if(T != NULL)
    {
        freenode(&T);
    }
    return 0;
}
