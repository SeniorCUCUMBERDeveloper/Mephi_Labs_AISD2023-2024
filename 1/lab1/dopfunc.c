#include "dopfunc.h"


int max(int seek, int seekNxt, FILE* f, int* indexmax)
{
    int buf;
    fseek(f, seek * sizeof(int), SEEK_SET);
    fread(&buf, sizeof(int), 1, f);
    int len = seekNxt - seek;
    *indexmax = 0;
    int result = buf;
    for(int i = 0; i < len - 1; i++)
    {
        fread(&buf, sizeof(int), 1, f);
        if(result < buf)
        {
            result = buf;
            *indexmax = i + 2;
        }
    }
    return result;
}


int min(int a, int b)
{
    if(a >= b)
    {
        return b;
    } else {
        return a;
    }
}


int input(FILE* f, Pair* pair)
{
                int* a;
                int lenmatrix;
                fread(&lenmatrix, sizeof(int), 1, f);
               (a) = malloc((lenmatrix + 1) *sizeof(int));
                for (int i = 0; i < lenmatrix + 1; i++)
                {
                    fread(&(a)[i], sizeof(int), 1, f);
               
                   
                }
               pair->offsets_f = a;
               
                return lenmatrix;
}


int addTask(FILE* f, FILE* f2,  Pair* pair, int lenmatrix)
{
    int count = 0;
    int indexk;
    int pos = 1;
    int k  = 0;
    int g = 0;
    int result = 3;
    int lastoofsets = 3 + lenmatrix;
    fwrite(&pos, sizeof(int), 1, f2);
    fwrite(&result, sizeof(int), 1, f2);
    fwrite(&lastoofsets, sizeof(int), 1, f2);
        for (int i = 0; i < lenmatrix; i++)
        {
                pos = ftell(f);
                int maxx = max(pair->offsets_f[i], pair->offsets_f[i+1], f, &indexk);
                fseek(f, pos, SEEK_SET);
                g = 0;
                
                for (int j = 0; j < lenmatrix; j++)
                {
                        if(indexk <= (pair->offsets_f[j+1] - pair->offsets_f[j])) g+=1;
                }
                k = min(pair->offsets_f[i+1] - pair->offsets_f[i], g); 
                fseek(f, pair->offsets_f[i] * sizeof(int), SEEK_SET);
                result = 0;
                int oor;
                for (int j = 0; j < k; j++)
                {
                        int buf;
                    fread(&buf, sizeof(int), 1, f);
                    pos = ftell(f);
                    maxx = max(pair->offsets_f[j], pair->offsets_f[j+1], f, &oor);
                    result += buf * max(pair->offsets_f[j], pair->offsets_f[j+1], f, &oor);
                    fseek(f, pos, SEEK_SET);
                 }
                 
                 
                 printf("\nresult = %d \n", result);
                 count += 1;
                 fwrite(&result, sizeof(int), 1, f2);
                 
        }
        return count;
}


int file(Pair* pair)
{
    char name[20], name1[20];
    int lenmatrix, count = 0;
    printf("Input Input_file.c\n");
    scanf("%s", name);
    printf("Input Output_file.c\n");
    scanf("%s", name1);
    if (strcmp(name, name1) == 0)
    {
        printf("Error");
        return -1;
    }
    FILE* f = fopen(name, "rb");
    FILE* f2 = fopen(name1, "wb");
    if (f != NULL)
    {
    lenmatrix = input(f, pair);
    count = addTask(f, f2,  pair, lenmatrix);
    fclose(f);
    fclose(f2);
    free(pair->offsets_f);
    return count;
    } else
    {
        printf("Input file not found....Exit\n");
        fclose(f2);
        return -1;
    } 
}

void printBin(int count)
{
        printf("Input file.b\n");
        char name[20];
        scanf("%s", name);
        int current;
        FILE* f = fopen(name, "rb");
        fread(&current, sizeof(int), 1, f);
        if (current != 1)
        {
                printf("It s not output bin\n");
                fclose(f);
                return;
        }
        int* a = malloc((2) * sizeof(int));
        for(int i = 0; i < 2; i++)
        {
                fread(&a[i], sizeof(int), 1, f);
        }
        if (f != NULL)
        {
            count = a[1] - a[0];
            for(int i = 0; i < count; i++)
            {
                fread(&current, sizeof(int), 1, f);
                printf("%d ", current);
            }
            printf("\n");
            fclose(f);
            free(a);
         }
         else {
                printf("Bin file not founded.....\n");
         } 
}
