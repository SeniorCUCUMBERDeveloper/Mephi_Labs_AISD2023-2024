#include "t.h"
#include "dialog.h"


int main(){
    Table* table = NULL;
    int rc;
    int (*fptr[])(Table**) = {NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Export, D_Allrelease, D_Onerelease, D_Remove}; 
    while(rc = dialog(msgs, NMsgs)){
        if (fptr[rc](&table) == 0){
            break;
        }
    }
    if(table != NULL)
    {
    	deleteTable(&table);
    }
    return 0;
}
