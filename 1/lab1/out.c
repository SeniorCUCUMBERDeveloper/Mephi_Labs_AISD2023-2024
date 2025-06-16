#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Input file.b\n");
	char name[20];
	scanf("%s", name);
	int max;
	int current;
	FILE* f = fopen(name, "rb");
	if (f != NULL)
	{
	    fseek(f, 3 * sizeof(int), SEEK_SET);
		printf("Input len of vector = ");
		scanf("%d", &max);
		for(int i = 0; i < max; i++)
		{
			fread(&current, sizeof(int), 1, f);
			printf("%d ", current);
		}
		printf("\n");
	}
	fclose(f);
	return 0;
}
