#include "lib.h"
#include "dialog.h"


int main(){
    Graph* T = create();
    int rc;
    const char* msgs[] = {"0.Quit", "1.D_Add_V", "2.D_Add_E", "3.D_Show", "4.D_Delete_E", "5.D_Delete_V", "6.D_Matrix", "7.D_Path", "8.D_DFS", "9.D_CC", "10.D_Correct", "11.D_Dot", "12.D_Primer", "13.D_Dop1", "14.D_Dop2", "15.D_Dop3", "16.D_Gen"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*fptr[])(Graph*) = {NULL, D_Add_V,D_Add_E, D_Show, D_Delete_E, D_Delete_V, D_Matrix,D_Path, D_DFS, D_CC, D_Correct, D_Dot, D_Primer, D_Dop1, D_Dop2, D_Dop3, D_Gen}; 
    while(rc = dialog(msgs, NMsgs)){
        if (fptr[rc](T) == 0){
            break;
        }
    }
    if(T != NULL)
    {
        destroyGraph(&T);
    }
    return 0;
}
