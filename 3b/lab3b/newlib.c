#include "t.h"



typedef struct KeySpace{
    char* key;
    int release;
    char* info;
    struct KeySpace* next;
}KeySpace;


typedef struct Table{
    KeySpace** ks;
    int len;
    int size;
}Table;


typedef struct ans{
    char** answer;
    int  size;
}ans;



int D_Add(Table** table)
{
        int flag = 0;
        printf("Input key\n");
        char* str = myreadline();
        char* data = myreadline();
        flag = push(table, str, data);
        if(flag == -1)
        {
            free(str);
            free(data);
            printf("Error, operation denied\n");
            return -1;
        }
        if(ratio(*table) >= 1 )
        {
                int easy = searchNexteasy(table);
                UpdateTable(table, easy);
        }
        return 1;
}


int D_Delete(Table** table)
{
        printf("Input key\n");
        char* str = myreadline();
        int flag = allpop(table, str);
        free(str);
        if(flag == -1){
        	printf("Error, operation denied\n");
        }
        return 1;
}


int D_Find(Table** table)
{
        printf("Input key\n");
        char* str = myreadline();
        int flag = copy(*table, str);
        if(flag == -1)
        {
        	printf("Error, operation denided\n");
        }
        free(str);
        return 1;
}


int D_Show(Table** table)
{
        int flag = printTable(*table);
        if (flag == -1)
        {
        	printf("Error, operation denied\n");
        }
        return 1;
}


int D_Import(Table** table)
{
        if(*table != NULL)
        {
        	deleteTable(table);
        }
        int flag = freadbin(table);
        if(flag == -1 && table == NULL)
        {
        	printf("Operation denied:(\n");
        	return -1;
        }
        return 1;
}


int D_Export(Table** table)
{
        if(*table == NULL)
        {
        	printf("Error, operation denied\n");
        	return -1;
        }
        int flag = fwritebin(*table);
        if(flag == -1)
        {
        	printf("File not found:(\n");
        	return -1;
        }
}

int D_Allrelease(Table** table)
{
        ans* answ = NULL;
        printf("Input key\n");
        char* str = myreadline();
        answ = findALLkey(*table, str);
        free(str);
                if(answ != NULL)
                {
                        for(int i = 0; i < (answ->size); i++)
                    {
                        printf("a - %s ", (answ->answer)[i]);    
                    }
                    free(answ->answer);
                    free(answ);
                    return 1;
                }
                printf("Error, operation denied\n");
        return -1;
}


int D_Onerelease(Table** table)
{
        int e;
        printf("Input key\n");
        char* str = myreadline();
        getInt(&e, "Input release\n");
        char** f = findRelease(*table, str, e);
        free(str);
        if(f != NULL)
        {
                printf("%s \n", *f);
                free(f);
                return 1;
        }
        printf("Error, operation denied");
        return -1;
}


int D_Remove(Table** table)
{
        int e;
        printf("Input key\n");
        char* str = myreadline();
        getInt(&e, "Input release\n");
        int flag = poprelease(table, str, e);
        if(flag == -1)
        {
                printf("Error, operation denied\n");
        }
        free(str);
        return 1;
}


int dialog(const char* msgs[], int N){
    char* errmsg = "";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for(i = 0; i < N; ++i){
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");
        n = getInt(&rc, ""); 
        if(n != 1){
            rc = -1;
        }
    } while(rc < 0);
    return rc;
}


char** findRelease(Table* table, char* key, int release)
{
    if(table == NULL || key == NULL || release < 1)
    {
        return NULL;
    }
    int j = hash(key, (table)->size);
    KeySpace* ptr = table->ks[j];
    while(ptr != NULL)
    {
        if(strcmp(key, ptr->key) == 0 && ptr->release == release)
        {
            char** ans = malloc(sizeof(char*));
            ans[0] = ptr->info;
            return ans;
        }
        ptr = ptr->next;
    }
    return NULL;
}


ans* findALLkey(Table* table, char* key)
{
    if(table == NULL || key == NULL)
    {
        return NULL;
    }
    int release = find(table, key);
    int j = hash(key, (table)->size);
    if(release < 1)
    {
        return NULL;
    }
    ans* answ = malloc(sizeof(ans));
    answ->answer = malloc(sizeof(char*) * release);
    answ->size = release;
    int i = 0;
    KeySpace* ptr = (table)->ks[j];
    while(ptr != NULL)
    {
        if(strcmp(ptr->key, key) == 0)
        {
            (answ->answer)[i] = ptr->info;
            i++;
        }
        if(i == release)
        {
            return answ;
        }
        ptr = ptr->next;
    }
}


int allpop(Table** table, char* key)
{
    if(table == NULL || key == NULL)
    {
        return -1;
    }
    int release = find(*table, key);
    if(release < 0)
    {
        return -1;
    }
    for(int i = release; i > 0; i--)
    {
        poprelease(table, key, i);
    }
    return 1;
}


int poprelease(Table** table, char* key, int release)
{
    if(table == NULL || key == NULL || release <= 0)
    {
        return -1;
    }
    int j = hash(key, (*table)->size);
    KeySpace* ptr_current = (*table)->ks[j];
    int r = find(*table, key);
    KeySpace* ptr_prev = (*table)->ks[j];
    while(ptr_current != NULL)
    {
        if(strcmp(ptr_current->key, key) == 0 && ptr_current->release == release)
        {
            free(ptr_current->key);
            free(ptr_current->info);
            if((*table)->ks[j] == ptr_current)
            {
                (*table)->ks[j] = ptr_current->next;
            }
            else{ 
                ptr_prev->next = ptr_current->next; 
            }
            if(r == 1)
            {
            	(*table)->len--;
            }
            free(ptr_current);
            correctTable(table, key, release, j);
            return 1;
        }
        ptr_prev = ptr_current;
        ptr_current = ptr_current->next;
    }
    return -1;
}


int correctTable(Table** table, char* key, int release, int j)
{
    KeySpace* ptr = (*table)->ks[j];
    while(ptr != NULL)
    {
        if(strcmp(ptr->key, key) == 0 && ptr->release > release)
        {
            ptr->release = ptr->release - 1;
        }else if(strcmp(ptr->key, key) == 0)
        {
            return 0;
        }
        ptr = ptr->next;
    }
    return 0;
}





int push(Table** table, char* key, char* data)
{
    if(*table == NULL || key == NULL)
    {
        return -1;
    }
    int release = find((*table), key);
    int j = hash(key, (*table)->size);
    if(release != -1)
    {
        KeySpace* ptr = malloc(sizeof(KeySpace));
        ptr->key = key;
        ptr->info = data;
        ptr->release = release + 1;
        ptr->next = (*table)->ks[j];
        (*table)->ks[j] = ptr;
        if(release == 0)
        {
        	(*table)->len++;
        }
        return 1;
    }
    return -1;
}


int find(Table* table, char* key)
{
    if(table == NULL || key == NULL)
    {
        return -1;
    }
    if(table->ks[hash(key, table->size)] == NULL)
    {
        return 0;
    }
    KeySpace* ptr = table->ks[hash(key, table->size)];
    while(ptr != NULL)
    {
        if(strcmp(ptr->key, key) == 0)
        {
            return ptr->release;
        }
        ptr = ptr->next;
    }
    return 0;
}


int copy(Table* table, char* key)
{
    int release = find(table, key);
    Table* copy = NULL;
    if(release > 0)
    {
        copy = malloc(sizeof(Table));
        copy->len = 0;
        copy->size = release;
        copy->ks = malloc(sizeof(KeySpace) * release);
        KeySpace* ptr = table->ks[hash(key, table->size)];
        for(int i = 0; i < copy->size; i++)
        {
            copy->ks[i] = malloc(sizeof(KeySpace));
            copy->ks[i]->key = calloc(strlen(key) + 1, sizeof(char));
            copy->ks[i]->next = NULL;
            strcpy(copy->ks[i]->key, key);
            while(ptr != NULL)
            {   
                if(strcmp(ptr->key, key) == 0){
                    copy->ks[i]->info = calloc(strlen(ptr->info) + 1, sizeof(char));
                    strcpy(copy->ks[i]->info, ptr->info);
                    copy->len++;
                    ptr = ptr->next;
                    break;
                }
                ptr = ptr->next;
            }
            copy->ks[i]->release = 1;
        }
        printTable(copy);
        deleteTable(&copy);
        return 1;
    }
    return -1;
}


int printTable(Table* table)
{
    if(table == NULL)
    {
        return -1;
    }
    for(int i = 0; i < table->size; i++)
    {
        printf("%d ", i);
        KeySpace* ptr = table->ks[i];
        if(ptr == NULL)
        {
            printf("%p", ptr);
        }
        while(ptr != NULL)
        {
            printf("%s ", ptr->key);
            printf("%d ", ptr->release);
            printf("%s ", ptr->info);
            ptr = ptr->next;
        }
        printf("\n");
    }
    return 1;
}


int deleteTable(Table** table)
{
    if(*table == NULL)
    {
        return -1;
    }
    for(int i = 0; i < (*table)->size; i++)
    {
        KeySpace* ptr =  (*table)->ks[i];
        while(ptr != NULL)
        {
            KeySpace* ptr2 = ptr;
            ptr = ptr->next;
            free(ptr2->info);
            free(ptr2->key);
            free(ptr2);
        }
    }
    free((*table)->ks);
    free(*table);
    *table = NULL;
    return 1;
}


int hash(char* str, int del)
{
    if(str == NULL)
    {
        return -1;
    }
    int count = 0;
    for(int i = 0; i < (int)strlen(str); i++)
    {
    	count += ((int)str[i] * ((unsigned int) pow(11, i) % del)) % del;
    }
    return count % del;
}


int freadbin(Table** table)
{
    char filename[20];
    char* key, *info;
    printf("Input file name _____.bin\n");
    scanf("%s", filename);
    FILE* f3 = fopen(filename, "rb");
    int n, len;
    if (f3 != NULL)
    {
        *table = malloc(sizeof(Table));
        fread(&n, sizeof(int), 1, f3);
        (*table)->size = n;
        (*table)->len = 0;
        (*table)->ks = malloc((*table)->size * sizeof(KeySpace));
        for(int i = 0; i < (*table)->size; i++)
        {
                (*table)->ks[i] = NULL;
        }
       while(1)
        {
            fread(&len, sizeof(int), 1, f3);
            if(feof(f3))
            {
               break;
            }
            key = calloc(len + 1, sizeof(char));
            fread(key, sizeof(char), len, f3);
            fread(&len, sizeof(int), 1, f3);
            info = calloc(len + 1, sizeof(char));
            fread(info, sizeof(char), len, f3);
            push(table, key, info);
        }
        fclose(f3);
        return 1;
    }
    return -1;
}


int fwritebin(Table* table)
{
    char filename[20];
    printf("Input file name ____.bin\n");
    scanf("%s", filename);
    FILE* f2 = fopen(filename, "wb");
    int len;
    if (f2 != NULL)
    {
        fwrite(&table->size, sizeof(int), 1, f2);
        for(int i = 0; i < table->size; i++)
        {
            KeySpace* ptr = table->ks[i];
            while(ptr != NULL)
            {
                len = (int)(strlen(ptr->key));
                fwrite(&len, sizeof(int),1,f2);
                fwrite(ptr->key, sizeof(char), len, f2);
                len = (int)(strlen(ptr->info));
                fwrite(&len, sizeof(int),1,f2);
                fwrite(ptr->info, sizeof(char), len, f2);
                ptr = ptr->next;
            }
        }
        fclose(f2);
        return 1;
    }
    fclose(f2);
    return -1;
}


char *myreadline()
{
    scanf("%*[\n]");
    int storage = 82;
    char* line1 = (char *) calloc(storage+1, sizeof(char));
    int len = 82;
    while(scanf("%82[^\n]", &line1[(len - storage)]) != 0) 
    {
        
        len += storage;
        line1 = (char *) realloc(line1, ((len) + 1) * sizeof(char));
    }
    line1[strlen(line1)] = '\0';
    line1 = (char *) realloc(line1, (strlen(line1) + 3) * sizeof(char));
    return line1;
}


int getInt(int* num, const char* pr)
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
        if ((res == 0 || res == 2))
        {
            printf("Incorrect symbol\n");
            printf("Please, try again = ");
            scanf("%*[^\n]");
        }
    }while(res != 1);
    return 1;
}


int ratio(Table* table)
{
    return (table)->len / (table)->size;
}


int searchNexteasy(Table** table)
{
	int count, num, copy;
	int is_easy;
	num = (*table)->size;
	count = num + 100;
	count = count - 1;
	int array[count];
	for (int i = 0; i < count; i++)
	{
        array[i] = i + 2;
	}
	for (int i = 0; i < count; i++)
	{
		copy = array[i];
     	is_easy = -1;
     	for (int j = i + 1; j < count; j++)
     	{
  			if ((array[j] % copy) == 0)
      		{
           		massiveCorrect(&array[0], j , count);
             	is_easy = 1;
                count--;
                j--;
       		}	
		}
      	if (is_easy == -1)
      	{
      		break;
      	}
	}
	for (int i = 0; i < count; i++)
    {
     	if ((num < array[i]) && ((*table)->len / array[i] < 1))
       	{
           	num = array[i];
            break;
        }
    }
  	return num;
}



void massiveCorrect(int* array, int i, int count)
{
		for (int k = i; k < count - 1; k++)
	    {
			(array)[k] = (array)[k + 1];
	    }			
}

int UpdateTable(Table** table, int new_size)
{
        Table* new = malloc(sizeof(Table));
        new->len = 0;
        new->size = new_size;
        new->ks = malloc(sizeof(KeySpace) * new->size);
        for(int i = 0; i < new->size; i++)
        {
                new->ks[i] = NULL;
        }
        for(int i = 0; i <(*table)->size; i++)
        {
                KeySpace* ptr = (*table)->ks[i];
                KeySpace* delete = ptr;
                while(ptr != NULL)
            {
                push(&new, ptr->key, ptr->info);
                ptr = ptr->next;
                free(delete);
                delete = ptr;
            }
               
         }
         free((*table)->ks);
         free(*table);
         *table = new;
}
