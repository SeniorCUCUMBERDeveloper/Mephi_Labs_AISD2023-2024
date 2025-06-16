#include "addfunc.h"


void outmatrToBin(Matrix* matrix)
{
	printf("Input file.b\n");
	char name[20];
	scanf("%s", name);
	FILE* f = fopen(name, "wb");
	if (f != NULL)
	{
		fwrite(&matrix->strings, sizeof(int), 1, f);
		int first = matrix->strings + 2;
		fwrite(&first, sizeof(int), 1, f);
		printf("len = %d\n", first);
		int len = first + matrix->matr[0].len; 
		printf("len = %d\n", len);
		for(int i = 1; i < matrix -> strings; i++)
		{
			fwrite(&len, sizeof(int),1, f);
			len += matrix->matr[i].len;
			printf("len = %d\n", len);
		}
		fwrite(&len, sizeof(int),1,f);	
		for (int i = 0; i < matrix -> strings; i++)
		{
			for(int j = 0; j < matrix -> matr[i].len; j++)
			{
				fwrite(&matrix->matr[i].array[j], sizeof(int), 1, f);
				printf("m = %d\n", matrix -> matr[i].array[j]);
			}
		}
	}
	fclose(f);
}



void outmatr(Matrix* matrix)
{
    int i, j;
    int *str;
    for (i = 0; i < matrix -> strings; i++)
    {
        str = matrix->matr[i].array;
        for (j = 0; j < matrix -> matr[i].len; j++)
        {
            printf("%d ", *(str + j));
        }
        printf("\n");
    }
}


int max(int* array, int n, int* h)
{
   int result = *array;
   *h = 0;
   for(int i = 0; i < n; i++)
   {
       if (*(array+i) > result)
       {
           result = *(array + i);
           *h = i;
       }
   }
    return result;
}


int min(int a, int b)
{
    if (a >= b)
    {
        return b;
    } 
    else {
        return a;
    }
}

int countK(int lenstring, Matrix* matrix)
{
        int k = 0;
        for(int i = 0; matrix->strings > i; i++)
        {
                if (lenstring <= matrix->matr[i].len)
                {
                        k+=1;
                }
        }
        return k;
}

int* vector(int* result, Matrix* matrix)
{
    int i, j;
    int h, l = 0;
    for(i = 0; i < matrix->strings; i++)
    {   
        int index = 0;
        int* strmax = matrix->matr[index].array;
        int* str = matrix->matr[i].array;
        int k = max(matrix->matr[i].array, matrix->matr[i].len, &h);
        int K = countK(h+1, matrix);
        for(j = 0; j < min(matrix->matr[i].len, K); j++)
        {
            *(result + i) += *(str + j) * max(strmax , matrix->matr[index].len, &l);
            index++;
            if (index < matrix->strings)
            {
                strmax = matrix->matr[index].array;
            }
        }
    }
    printf("\n");
    return result;
}
