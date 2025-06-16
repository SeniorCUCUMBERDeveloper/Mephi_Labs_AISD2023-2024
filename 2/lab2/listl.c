#include "list.h"


typedef struct data
{
    char* id;
    int ts;
    int ta;
}data;


typedef struct list{
    void* data;
    struct list *next;
}list;


typedef struct queue{
    list* head;
    list* tail;
}queue;


typedef struct Airport{
    queue** qq;
}Airport;


void InputAirport(Airport** mass, int num)
{	
		*mass = malloc(sizeof(Airport));
       (*mass)->qq = malloc(num * sizeof(queue*));
        for (int i = 0; i < num; i++)
        {
           (*mass)->qq[i] =  malloc(sizeof(queue));
           (*mass)->qq[i]->head = NULL;
           (*mass)->qq[i]->tail = NULL;
           (*mass)->qq[i]->head = (*mass)->qq[i]->tail; 
        }
        return;
}


void freeAirport(Airport* mass, int num){
        for(int j = 0; j < num; j++)
        {
             free(mass->qq[j]);
        }
        free(mass->qq);
        free(mass);
        return;
}
list* topPut(queue* q);
void Input(queue** q)
{
        *q = malloc(sizeof(queue));
    (*q)->head = NULL;
    (*q)->tail = NULL;
   (*q)->head = (*q)->tail;
    return;
}


void freequeue(queue* q)
{
        free(q);
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


char* inputKeyBoard(queue* Time, int* len, int* num)
{
        char* InputLine = myreadline();
        char* t = strtok(InputLine, "/ ");
        int count = 0;
        *num = atoi(t);
        int field2 = 0;
        char* str;
        *len = 0;
        data* dat;
        while(t != NULL)
        {   
            if (count == 1)
            {
                str = t;
            }
            if (count == 2)
            {
                field2 = atoi(t);
            }
            if (count == 3)
            {
                int n = atoi(t);
                dat = makedata(str, field2, n);
                put(Time, dat);
                count = 0;
                *len += 1;
            }
                t = strtok(NULL, "/ ");
                count++;
        }
        return InputLine;
}


void printq(queue* q, int flag)
{
    list* ptr = q->head;
    if (ptr == NULL){
        printf("Empty\n");
        return;
    } else
    {
        while(ptr)
        {
            if(flag == 0)
            {
                printf("%s ", ((data*)(ptr->data))->id);
                printf("%d ", ((data*)(ptr->data))->ta);
                printf("%d", ((data*)(ptr->data))->ts);
                printf("\t");
            }
            else
            {
                printf("%s ", ((data*)(ptr->data))->id);
            }
            ptr = ptr->next;
        }
        printf("\n");
    }
    return;
}


void bubbleSort(queue* q, int len)
{
    data* tmp = malloc(sizeof(data));
    for (int i = 0; i < len - 1; i++)
    {
        list* ptr = q->head;
        for (int j = 0; j < len -1; j++)
        {
            if (ptr != NULL && ptr->next != NULL && (((data*)(ptr->data))->ta > ((data*)(ptr->next->data))->ta)) 
            {
                tmp->id = ((data*)(ptr->next->data))->id; 
                tmp->ta = ((data*)(ptr->next->data))->ta; 
                tmp->ts = ((data*)(ptr->next->data))->ts; 
                ((data*)(ptr->next->data))->id = ((data*)(ptr->data))->id;
                ((data*)(ptr->next->data))->ta = ((data*)(ptr->data))->ta;
                ((data*)(ptr->next->data))->ts = ((data*)(ptr->data))->ts;
                ((data*)(ptr->data))->id = tmp->id;
                ((data*)(ptr->data))->ta = tmp->ta;
                ((data*)(ptr->data))->ts = tmp->ts;
            }
           ptr = ptr->next;
        }
    }
    free(tmp);
}


Airport* individualTask(queue* Time, Airport* mass, int num, int len)
{
            int i = 0;
            data* dat;
            int Timer = 1;
            list* ptr1;
            int count = 0;
            int print = 0;
            int* time_ = calloc(num, sizeof(int));
            while (len != count)
            {
                if(Time->head != NULL)
                {
                   ptr1 = Time->head;
                    while(ptr1 != NULL)//ptr1
                    {
                       if(Timer == ((data*)(ptr1->data))->ta)
                        {
                            if(mass->qq[i]->head == NULL)
                            {
                               time_[i] = ((data*)(ptr1->data))->ta;
                            
                            }
                            ptr1 = ptr1 -> next;
                            list* p = topPut(Time);
                            dat = makedata(((data*)(p->data))->id, ((data*)(p->data))->ta, ((data*)(p->data))->ts);
                            put(mass->qq[i], dat);
                            print = 1;
                            free(p->data);
                            free(p);
                            i++;
                            if (i == num)
                            {
                                i = 0;
                            }                
                        }
                        else{
                            break;
                        }
                    }
                }
                for(int j = 0; j < num; j++)
                {
                   if(mass->qq[j]->head != NULL)
                   {
                       ptr1 = mass->qq[j]->head;
                       while(ptr1 != NULL)
                       {
                           if (Timer == ((((data *)ptr1->data)->ts) + time_[j]))
                           {
                               ptr1 = ptr1->next;
                               pop(mass->qq[j]);
                               print = 1;
                               time_[j] = Timer;
                               count += 1;
                           }
                           else{
                               break;
                           }
                       }
                   }
                }
                if (print == 1)
                {
                        printf("%d\n", Timer);
                        for(int j = 0; j < num; j++)
                        {
                            
                            printf("N%d ",j + 1);
                            printq(mass->qq[j], 1);
                        }
                }
                print = 0;
                Timer += 1;
            }
            free(time_);
            return mass;
}


data* makedata(char* str, int x, int y)
{
    data* ptr = malloc(sizeof(data));
    ptr->ta = x;
    ptr->ts = y;
    ptr->id = str;
    return ptr;
}


void put(queue* q, void* data)
{
    list* ptr = malloc(sizeof(list));
    ptr->data = data;
    ptr->next = NULL;
    if (q->head == NULL)
    {
        q->tail= ptr;
        q->head = q->tail;
    }
    else
    {
        q->tail->next = ptr;
        q->tail = ptr;
    }
    return;
}


list* topPut(queue* q)
{
    list* tmp = q->head;
    if(q->head != NULL)
    {
        list* ptr = malloc(sizeof(list));
        ptr->data = malloc(sizeof(data));
        ((data*)(ptr->data))->id = ((data*)(q->head->data))->id;
        ((data*)(ptr->data))->ta = ((data*)(q->head->data))->ta;
        ((data*)(ptr->data))->ts = ((data*)(q->head->data))->ts;
        ptr->next = NULL;
        q->head = q->head->next;
        free(tmp->data);
        free(tmp);
        return ptr;
    }
    return 0;
}


void* pop(queue* q)
{
    list* tmp;
    if (q->head != NULL)
    {
        tmp = q->head;
        q->head = q->head->next;
        free(tmp->data);
        free(tmp);
    }
    return NULL;
}
