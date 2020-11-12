#include<stdio.h>
#include<stdlib.h>
#define MAX 10

int *arr;
int head = -1;

void push(int data);
void pop(void);
void top(void);
int isEmpty(void);
void display(void);
void freeList(void);

int main(void)
{
    arr = (int*) malloc(sizeof(int)*MAX);

    int a = isEmpty();
    if(a == 1)
    {
        printf("works\n");
    }

    int numbers[5] = {5, 10, 15, 20, 25};

    for(int i = 0; i<5; i++)
    {
        push(numbers[i]);
    }
    display();
    top();
    pop();
    top();
    pop();

    a = isEmpty();
    if(a == 1)
    {
        printf("something wrong\n");
    }
    push(100);
    display();
    freeList();
}

void push(int data)
{
    if(head == MAX)
    {
        printf("Not Enough memory!\n");
    }
    else
    {
        head++;
        arr[head] = data;
    }
}

void pop(void)
{
    if(head == -1)
    {
        printf("Stack is empty!\n");
    }
    else
    {
        head--;
    }
}

void top(void)
{
    printf("%d\n", arr[head]);
}

int isEmpty(void)
{
    if(head == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void display(void)
{
    for(int i = 0; i<=head; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void freeList(void)
{
    free(arr);
}