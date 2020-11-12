#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int number;
    struct node* next;
}node;

node *head;

void push(int data);
void pop(void);
void top(void);
int isEmpty(void);
void display(void);
void freeList(void);

int main(void)
{
    int a = isEmpty();
    if(a == 1)
    {
        printf("empty\n");
    }

    int arr[5] = {5, 10, 15, 20, 25};

    for(int i = 0; i<5; i++)
    {
        push(arr[i]);
    }
    display();
    pop();
    pop();
    display();
    push(100);
    display();
    pop();
    top();

    a = isEmpty();
    if(a == 1)
    {
        printf("Something bad happened!\n");
    }
    display();
    freeList();
}

void push(int data)
{
    node *temp = (node *) malloc(sizeof(node));
    temp->number = data;
    temp->next = head;
    head = temp;
}

void pop(void)
{
    node *temp = head;
    head = head->next;
    free(temp);
}

void top(void)
{
    printf("%d\n", head->number);
}

int isEmpty(void)
{
    if(head == NULL)
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
    node * temp = head;
    while(temp != NULL)
    {
        printf("%d  ", temp->number);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(void)
{
    while(head != NULL)
    {
        node *temp = head->next;
        free(head);
        head = temp;
    }
}