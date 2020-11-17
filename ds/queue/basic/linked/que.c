#include<stdlib.h>
#include<stdio.h>

typedef struct node
{
    int data;
    struct node* next;
}node;

typedef struct queue
{
    node* head;
    node* tail;
}queue;

void initQue(queue *a);
void enQue(queue *a, int x);
int deQue(queue *a);
void freeMemory(queue *a);


int main(void)
{
    queue *numOne = (queue*) malloc(sizeof(queue)*1);
    initQue(numOne);

    queue *numTwo = (queue*) malloc(sizeof(queue)*1);
    initQue(numTwo);

    for(int i = 1; i < 10; i = i + 2)
    {
        enQue(numOne, i);
    }

    for(int i = 0; i < 10; i = i+2)
    {
        enQue(numTwo, i);
    }

    printf("1st queue: ");
    while(numOne->head != NULL)
    {
        printf("%d  ", deQue(numOne));
    }
    deQue(numOne);

    printf("\n2nd queue: ");
    while(numTwo->head != NULL)
    {
        printf("%d  ", deQue(numTwo));
    }
    deQue(numTwo);

    printf("2nd queue(1): ");
    enQue(numTwo, 1000);
    enQue(numTwo, 2000);
    enQue(numTwo, 3000);
    enQue(numTwo, 4000);
    enQue(numTwo, 5000);
    while(numTwo->head != NULL)
    {
        printf("%d  ", deQue(numTwo));
    }
    deQue(numTwo);

    freeMemory(numOne);
    freeMemory(numTwo);
}

void initQue(queue *a)
{
    a->head = NULL;
    a->tail = NULL;
}

void enQue(queue *a, int x)
{
    node *temp = (node *) malloc(sizeof(node)*1);

    temp->data = x;
    temp->next = NULL;

    if(a->head == NULL)
    {
        a->tail = a->head = temp;
        return;
    }

    a->tail->next = temp;
    a->tail = temp;
}

int deQue(queue *a)
{
    if(a->head == NULL)
    {
        printf("No element in the queue!\n");
    }
    else
    {
        node* temp = a->head;
        a->head = a->head->next;

        int x = temp->data;
        free(temp);
        return x;
    }
}

void freeMemory(queue *a)
{
    while(a->head != NULL)
    {
        node*temp = a->head;
        a->head = a->head->next;
        free(temp);
    }
    free(a);
}