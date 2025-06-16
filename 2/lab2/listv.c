#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 4


typedef struct data
{
    char* id;
    int ta;
    int ts;
}data;


typedef struct queue
{
    void* Value[MAX];
    int head, tail, size;
}queue;


typedef struct Airport
{
    queue** qq;
}Airport;


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


void Input(queue** q)
{
	*q = malloc(sizeof(queue));
    (*q)->head = 0;
    (*q)->tail = 0;
    (*q)->size = 0;
    return;
}


void put(queue* q, void* data)
{
    if(q->tail < MAX)
    {
        q->Value[q->tail] = data;
        q->tail = q->tail + 1;
        q->size = q->size + 1;
    }
    else
    {
        printf("Queue if Full, operation denied\n");
        free(data);
    }
    return;
}


void* pop(queue* q)
{
    if (q->size == 0)
    {
        printf("Empty\n");
        return NULL;
    }
    else
    {
        void* data = q->Value[q->head];
        q->head = q->head + 1;
        q->size = q->size - 1;
        return data;
    }
}

data* makedata(char* str, int x, int y)
{
    data* ptr = malloc(sizeof(data));
    ptr->ta = x;
    ptr->ts = y;
    ptr->id = str;
    return ptr;
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
    if (q->size == 0)
    {
        printf("Empty\n");
        return;
    } else{
            for(int i = q->head; i < q->tail; i++)
            {
                if (flag == 0)
                {
                    printf("%s ", ((data*)(q->Value[i]))->id);
                    printf("%d ", ((data*)(q->Value[i]))->ta);
                    printf("%d", ((data*)(q->Value[i]))->ts);
                    printf("\t");
                } else
                {
                    printf("%s ", ((data*)(q->Value[i]))->id);
                }
            }
        printf("\n");
        
    }
    return;
}


void bubbleSort(queue* q, int len)
{
    data* tmp;
    for (int i = 0; i < q->tail - 1; i++)
    {
        for (int j = 0; j < q->tail - 1; j++)
        {
            if ((q->size > 0) && (((data*)(q->Value[j]))->ta > ((data*)(q->Value[j + 1]))->ta)) 
            {
                tmp = ((data*)(q->Value[j+1]));
                ((q->Value[j+1])) = ((q->Value[j]));
                (q->Value[j]) = tmp;
            }
        }
    }
}


Airport* individualTask(queue* Time, Airport* mass, int num, int len)
{
            int i = 0;
            data* dat;
            int Timer = 1;
            int ptr1;
            int count = 0;
            len = Time->size;
            int print = 0;
            int* time_ = calloc(num, sizeof(int));
            while (len != count)
            {
                if(Time->head != Time->tail)
                {
                   ptr1 = Time->head;
                    while(ptr1 != Time->tail)
                    {
                       if(Timer == ((data*)(Time->Value[ptr1]))->ta)
                        {
                            if(mass->qq[i]->head == mass->qq[i]->tail)
                            {
                               time_[i] = (((data*)(Time->Value[ptr1]))->ta);
                            
                            }
                            ptr1 = ptr1 + 1;
                            data* p = pop(Time);
                            dat = makedata(((data*)(p))->id, ((data*)(p))->ta, ((data*)(p))->ts);
                            put(mass->qq[i], dat);
                            print = 1;
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
                   if(mass->qq[j]->head != mass->qq[j]->tail)
                   {
                       ptr1 = mass->qq[j]->head;
                       while(ptr1 != mass->qq[j]->tail)
                       {
                           if (Timer == ((((data *)mass->qq[j]->Value[ptr1])->ts) + time_[j]))
                           {
                               ptr1 = ptr1 + 1;
                               data*  p = pop(mass->qq[j]);
                               free(p);
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


void freeAirport(Airport* mass, int num){
        for(int j = 0; j < num; j++)
        {
             free(mass->qq[j]);
        }
        free(mass->qq);
        free(mass);
        return;
}


void InputAirport(Airport** mass, int num)
{
        *mass = malloc(sizeof(Airport));
        (*mass)->qq = malloc(num * sizeof(queue*));
        for (int i = 0; i < num; i++)
        {
           (*mass)->qq[i] =  malloc(sizeof(queue));
           (*mass)->qq[i]->head = 0;
           (*mass)->qq[i]->tail = 0;
        }
        return;
}
