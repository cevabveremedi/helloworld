#include<stdio.h>
#include<stdlib.h>

typedef struct input
{
    int number;
    int priority;
}input;

typedef struct node
{
    input data;
    struct node* next;
}node;

node* head = NULL;
node* tail = NULL;

void push(input x);
int pop(void);

int main(void)
{
    input a, b, c, d;

    a.number = 5;
    a.priority = 0;

    b.number = 10;
    b.priority = 0;

    c.number = 15;
    c.priority = 1;

    d.number = 20;
    d.priority = 0;

    push(a);
    push(b);
    push(c);
    push(d);

    for(int i = 0; i<4; i++)
    {
        printf("%d  ", pop());
    }

    push(d);
    printf("%d ", pop());
    printf("%d", pop());
}

void push(input x)
{
    node* temp = (node*)malloc(sizeof(node));
    
    temp->data = x;
    temp->next = NULL;

    if(head == NULL)
    {
        head = tail = temp;
        return;
    }
    else if(x.priority == 1)
    {
        temp->next = head;
        head = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}

int pop(void)
{
    if(head == NULL)
    {
        printf("No element in the queue! \n");
        return 0;
    }
    else
    {
        node* temp = head;
        head = head->next;

        int x = temp->data.number;
        free(temp);

        return x;
    }
}