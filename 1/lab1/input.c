#include "input.h"


int addString(Matrix* matrix)
{
    int i,j,n;
    for(i = 0; i < matrix->strings; i++)
    {
        if (getInt(&n, "Input count of strings = ",1) == 0)
        {
            matrix->strings = i;
            delmatrix(matrix);
            return 0;
        }
        matrix->matr[i].len = n;
        matrix->matr[i].array = (int*)calloc(matrix->matr[i].len, sizeof(int));
        for(j = 0; j < matrix -> matr[i].len; j++)
        {
            if (getInt(matrix->matr[i].array + j, "Input element = ", 0) == 0)
            {
                matrix->strings = i + 1;
                delmatrix(matrix);
                return 0;
            }
        }
    }
    return 1;
}

int inputmatr(Matrix* matrix)
{
    int n;
    if (getInt(&n, "Input number of lines = ", 1) == 0)
    {
        return 0;
    }
    matrix->strings = n;
    matrix->matr = (String *)malloc(n *  sizeof(String));
    if (addString(matrix) == 0)
    {
        return 0;
    }
    return 1;
}


int getInt(int* num, const char* pr, int flag)
{
    int res = 0;
    int e;
    printf("%s ", pr);
    do{
        res = scanf("%d.%d", num, &e);
        if (res < 0 || res == EOF )
        {
        	printf("EOF\n");
            return 0;
        }
        if(flag == 1 &&  res == 1)
        {
        	if (*num < 1){
	            printf("Count of strings/elements > 0\n");
	            printf("You have one more try = ");
	            res = 12;
            }
        }
        if ((res == 0 || res == 2))
        {
            printf("Incorrect symbol\n");
            printf("Please, try again = ");
            scanf("%*[^\n]");
        }
    }while(res != 1);
    return 1;
}


void delmatrix(Matrix* matrix)
{
    int i;
    for (i = 0; i < matrix->strings; i++)
    {
        free(matrix->matr[i].array);
    }
    free(matrix->matr);
    matrix->matr = NULL;
    matrix->strings = 0;
}
