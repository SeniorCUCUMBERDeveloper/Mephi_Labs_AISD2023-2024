#include "dopfunc.h"


int main()
{
        Pair pair;
        int count;
        count = file(&pair);
        if (count == - 1)
        {
                printf("Error\n");
        } 
        else
        {
                printBin(count);
        }
        return 0;
}
