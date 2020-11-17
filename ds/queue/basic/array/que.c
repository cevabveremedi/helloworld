#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
    int head;
    int tail;
    int size;
    int *elements;
}queue;

void initQue(queue* a, int s);
void enQue(queue* a, int s);
int deQue(queue* a);

int main(void)
{
    queue* one = (queue*)malloc(sizeof(queue)*1);
    initQue(one, 10);

    for(int i = 1; i<=10; i++)
    {
        enQue(one, i);
    }

    for(int i = 0; i<10; i++)
    {
        printf("%d  ", deQue(one));
    }
    enQue(one, 10);
    enQue(one, 20);
    enQue(one, 30);
    enQue(one, 40);

    printf("\n");
    for(int i = 0; i<4; i++)
    {
        printf(" %d  ", deQue(one));
    }
    enQue(one, 59);
    printf("  %d  ", deQue(one));
    
    printf("\n");
    for(int i = 0; i < one->size; i++)
    {
        printf("   %d ", one->elements[i]);
    }
}

void initQue(queue* a, int s)
{
    a->head = -1;
    a->tail = -1;
    a->size = s;
    a->elements = (int *) malloc(sizeof(int)*s);
}

void enQue(queue* a, int s)
{
    a->tail = (a->tail + 1) % a->size;
    a->elements[a->tail] = s;
}

int deQue(queue* a)
{
    if(a->head == a->tail)
    {
        printf("No elements in the queue!\n");
    }
    else
    {
        a->head = (a->head + 1) % a->size;
        return a->elements[a->head];
    }
}