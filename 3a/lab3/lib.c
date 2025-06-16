#include "t.h"


typedef struct info{
    int info;
}info;


typedef struct Node{
    int release;
    info* data;
    struct Node *next;
}Node;


typedef struct KeySpace {
    char* key;
    Node *node;
}KeySpace;


typedef struct Table{
    KeySpace *ks;
    int capacity;
    int len;
}Table;


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


int D_Add(Table** table)
{
        int flag = 0;
        int e;
        printf("Input key\n");
        char* str = myreadline();
        getInt(&e, "Input data for add\n");
        info* data = malloc(sizeof(info));
        data->info = e;
        flag = push(table, str, data);
        if(flag != 0)
        {
                free(str);
        }
        if(flag == -1)
        {
            free(data);
            printf("Error, operation denied\n");
        }
        return 1;
}


int D_Delete(Table** table)
{
        printf("Input key\n");
        char* str = myreadline();
        int flag = pop(*table, str);
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
        table = intxt(table);
        if(table == NULL)
        {
        	return -1;
        }
        return 1;
}


int D_New(Table** table)
{
        int e;
        printf("Input key\n");
        char* str = myreadline();
        getInt(&e, "Input release\n");
        Table* new = individual1(*table, str, e);
        free(str);
        if(new == NULL)
        {
            printf("Error, operation denied\n");
            return -1;
        }
        printTable(new);
        removeTable(new);
        return 1;
}


int D_Remove(Table** table)
{
        int e;
        printf("Input key\n");
        char* str = myreadline();
        getInt(&e, "Input release\n");
        int flag = poprelease(*table, str, e);
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


int printTable(Table* table)
{
    if(table == NULL)
    {
        return -1;
    }
    if(table->len == 0)
    {
        return -1;
    }
    for(int i = 0; i < table->len; i++)
    {
        printf("N%d ", i);
        printf("%s ", table->ks[i].key);
        Node* ptr = table->ks[i].node;
        while(ptr != NULL)
        {
                printf("%d ", ptr->release);
            printf("%d ", ptr->data->info);
            ptr = ptr->next;
        }
        printf("\n");
    }
    return 0;
}


int searchTable(Table* table, char* key)
{
    if(table == NULL || key == NULL || table->len == 0)
    {
        return -1;
    }
    int i = 0;
    for(i = 0; i < table->len; i++)
    {
        if(strcmp(table->ks[i].key, key) == 0)
        {
            return i;
        }
    }
    return -1;
}


int  copy(Table* table, void* key)
{
    if(table == NULL)
    {
        return -1;
    }
    if(table->len == 0)
    {
        return -1;
    }
    int i = searchTable(table, key);
    if(i == -1)
    {
        return -1;
    }
    Node* ptr = table->ks[i].node;
    while(ptr != NULL)
    {
        printf("%d %d ",ptr->release,  ptr->data->info);
        ptr = ptr->next;
    }
    return 0;
}


int push(Table** table, void* key, void* data)
{
    if(*table == NULL || key == NULL || data == NULL){
        return -1;
    }
    int i = searchTable(*table, key);
    if(i >= 0)
    {
        Node* ptr = malloc(sizeof(Node));
        ptr->release = (rand() % 100) + 1;
        ptr->data = data;
        ptr->next = (*table)->ks[i].node;
        (*table)->ks[i].node = ptr;
        return 1;
    }else if((*table)->len < (*table)->capacity){
        (*table)->ks[(*table)->len].key = key;
        (*table)->ks[(*table)->len].node = malloc(sizeof(Node));
        (*table)->ks[(*table)->len].node->release = 0;
        (*table)->ks[(*table)->len].node->data = data;
        (*table)->ks[(*table)->len].node->next = NULL;
        (*table)->len++;
        return 0;
    }else if((*table)->len >= (*table)->capacity)
    {
        free(data);
    }
    return -1;
}


int pop(Table* table, void* key)
{
    if(table == NULL || table->len == 0 || key == NULL)
    {
        return -1;
    }
    int i = searchTable(table, key);
    if(i == -1)
    {
        return -1;
    }
    Node* ptr;
    while(table->ks[i].node != NULL)
    {
        ptr = table->ks[i].node;
        table->ks[i].node = table->ks[i].node->next;
        ptr->next = NULL;
        free(ptr->data);
        free(ptr);
    }
    free(table->ks[i].key);
    table->ks[i].key = table->ks[table->len-1].key;
    table->ks[i].node = table->ks[table->len - 1].node;
    table->ks[table->len-1].key = NULL;
    table->ks[table->len - 1].node = NULL;
    table->len--;
    return 0;
}


void* individual1(Table* table, void* key, int release)
{
    if(table == NULL || table->len == 0 || key == NULL)
    {
        return NULL;
    }
    int i = searchTable(table, key);
    if(i == -1)
    {
        return NULL;
    }
    Node* ptr = table->ks[i].node;
    Table* new = calloc(1, sizeof(Table));
    (new)->capacity = table->capacity;
    (new)->len = 0;
   (new)->ks = malloc(new->capacity * sizeof(KeySpace));
    int j = 0;
    if(release == -1)
    {
        while(ptr != NULL)
        {
            info* data = malloc(sizeof(info));
            data->info = ptr->data->info;
            if((new)->len != new->capacity)
            {
                new->ks[j].key = calloc(2, sizeof(char));
                new->ks[j].key[0] = rand()%(new->capacity);
                new->ks[j].key[1] = '\0';
            }
            push(&new, new->ks[j].key, data);
            j++;
            ptr = ptr->next;
            if(j == new->capacity)
            {
                j = 0;
            }
        }
    }else{
        info* data = malloc(sizeof(info));
        while(ptr != NULL)
        {
            if(release == ptr->release)
            {
                new->ks[j].key = calloc(2, sizeof(char));
                new->ks[j].key[0] = rand()%(new->capacity);
                new->ks[j].key[1] = '\0';
                data->info = ptr->data->info;
                push(&new, new->ks[j].key, data);
            }
            ptr = ptr->next;
        }
    }
    return new;
}


void removeTable(Table* t)
{
    for(int i = 0; i < t->len; i++)
    {
        while(t->ks[i].node != NULL)
        {
            Node* ptr = t->ks[i].node;
            t->ks[i].node = t->ks[i].node->next;
            free(ptr->data);
            free(ptr);
        }
        free(t->ks[i].key);
    }
    free(t->ks);
    free(t);
}


int poprelease(Table* t, char* key, int release)
{
    if(t == NULL || t->len == 0 || key == NULL)
    {
        return -1;
    }
    int i = searchTable(t, key);
    if(i == -1)
    {
        return -1;
    }
    Node* ptr = t->ks[i].node;
    if(release == ptr->release && ptr->next == NULL)
    {
        free(ptr->data);
        free(ptr);
        free(t->ks[i].key);
        t->ks[i].key = t->ks[t->len-1].key;
        t->ks[i].node = t->ks[t->len - 1].node;
        t->ks[t->len-1].key = NULL;
        t->ks[t->len - 1].node = NULL;
        t->len--;
        return 0;
    }
    else if(release == ptr->release && ptr->next != NULL)
    {
        t->ks[i].node = t->ks[i].node->next;
        free(ptr->data);
        free(ptr);
        return 0;
    }
    Node* prev = ptr;
    while(ptr != NULL)
    {
        if(ptr->release == release)
        {
            prev->next = ptr->next;
            free(ptr->data);
            free(ptr);
            return 0;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return -1;
}


char* myread(FILE* f, char* line1)
{
    int storage = 82;
    line1 = (char *) calloc(storage+1, sizeof(char));
    int len = 82;
    while(fscanf(f, "%82[^\n]", &line1[(len - storage)]) != 0) 
    {
        
        len += storage;
        line1 = (char *) realloc(line1, ((len) + 1) * sizeof(char));
    }
    line1[strlen(line1)] = '\0';
    line1 = (char *) realloc(line1, (strlen(line1) + 3) * sizeof(char));
    return line1;
}


void* intxt(Table** table)
{
    char name2[20];
    printf("Input file name .txt\n");
    scanf("%s", name2);
    FILE* fd = fopen(name2, "r");
    if (fd != NULL)
    {
        if (*table != NULL)
        {
            removeTable(*table);   
        }
        int capacity, len;
        fscanf(fd, "%d", &capacity);
        fscanf(fd, "%d", &len);
        *table = malloc(sizeof(Table));
        (*table)->capacity = capacity;
        (*table)->len = len;
        (*table)->ks = malloc((*table)->capacity * sizeof(KeySpace));
        char* str;
        Node* ptr;
         for (int i = 0; i < (*table)->len; i++)
         {
               fscanf(fd, "%*[\n]");
               str = myread(fd, str);
               int count = 0;
               char* s = strtok(str, " ");
               (*table)->ks[i].key = s;
               while(s != 0)
               {
               
                   if(count == 1)
                   {
                        info* data = calloc(1, sizeof(info));
                        data->info = atoi(s);
                        (*table)->ks[i].node = malloc(sizeof(Node));
                        (*table)->ks[i].node->release = 1;
                        (*table)->ks[i].node->data = data;
                        (*table)->ks[i].node->next = NULL;
                        ptr = (*table)->ks[i].node;
                   }
                   if(count > 1)
                   {
                       info* data = calloc(1, sizeof(info));
                       data->info = atoi(s);
                       Node* p = malloc(sizeof(Node));
                       p->release = ptr->release + 1;
                       p->data = data;
                       p->next = NULL;
                       ptr->next = p;
                       ptr = p;
                   }
                   s = strtok(NULL, " ");
                   count++;
               }
         }
         fclose(fd);
    }
    else
    {
        printf("Файла не существует\n");
    }
    printf("table\n");
    return *table;
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
