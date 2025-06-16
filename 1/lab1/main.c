#include "input.h"
#include "addfunc.h"


int main()
{
    Matrix matrix = {0, NULL};
    if (inputmatr(&matrix) == 0)
    {
        return 0;
    }
    int* result = (int*)calloc(matrix.strings, sizeof(int));
    result = vector(result,  &matrix);
    printf("Original matrix\n");
    outmatr(&matrix);
    printf("Resulting vector\n");
    for(int i = 0; i < matrix.strings; i++)
    {
        printf("%d ", *(result + i));
    }
    outmatrToBin(&matrix);
    delmatrix(&matrix);
    free(result);
    return 0;
}
