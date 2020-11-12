#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

node* Head = NULL;
int totalNode = 0;

node * getNode(int x)
{
    node *new = (node *) malloc(sizeof(node)*1);
    new->number = x;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

void displayList(void)
{
    if(totalNode == 0)
    {
        printf("List is Empty!\n");
    }
    else
    {
        node *temp = Head;

        while(temp != NULL)
        {
            printf("%d  ", temp->number);
            temp = temp->next;
        }
        printf("(Total: %d)\n", totalNode);
    }
}

void displayListReverse(void)
{
    if(totalNode == 0)
    {
        printf("List is Empty!\n");
    }
    else
    {
        node *temp = Head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        while(temp != NULL)
        {
            printf("%d  ", temp->number);
            temp = temp->prev;
        }
        printf("(Total: %d)\n", totalNode);
    }
}

void invertList(void)
{
    node* tail = Head;
    while(tail->next != NULL)
    {
        tail = tail->next;
    }

    node* temp = Head;
    while(temp != NULL)
    {
        node *ptr = temp->next;
        temp->next = temp->prev;
        temp->prev = ptr;
        temp = temp->prev;
    }

    Head = tail;
}

int deleteNode(int position)
{
    if(position < 1 || position > totalNode)
    {
        printf("Invalid position!\n");
        return -1;
    }

    node *temp = Head;

    if(position == 1)
    {
        if(Head->next == NULL)
        {
            free(temp);
        }
        else
        {
            Head = Head->next;
            free(temp);
            Head->prev = NULL;
        }
    }
    else if(position == totalNode)
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        node *prevv = temp->prev;
        free(temp);
        prevv->next = NULL;
    }
    else
    {
        for(int i = 1; i<position; i++)
        {
            temp = temp->next;
        }
        node *prevv = temp->prev;
        node *nextt = temp->next;

        prevv->next = nextt;
        nextt->prev = prevv;
        free(temp);
    }
    totalNode--;
    return 1;
}

void showElement(int oldPos)
{
    node *temp = Head;

    for(int i = 1; i<=totalNode; i++)
    {
        if(i == oldPos)
        {
            printf("|%d|  ", temp->number);
        }
        else
        {
            printf("%d  ", temp->number);
        }
        temp = temp->next;
    }

    printf("(Position %d selected)\n", oldPos);
}

void changePosition(void)
{
    int oldPos = 0, newPos = 0;
    do
    {
        printf("Which element's position will change: ");
        scanf("%d", &oldPos);
    } while (oldPos < 1 || oldPos > totalNode);
    
    showElement(oldPos);

    do
    {
        printf("\nNew position: ");
        scanf("%d", &newPos);
    } while (newPos < 1 || newPos > totalNode);

    insertNode(1, 0);
    insertNode(totalNode+1, 0);

    node *temp = Head;
    node *old = NULL;
    node *new = NULL;

    if(newPos > oldPos)
    {
        for(int i = 0; i<totalNode; i++)
        {
            if(i == oldPos)
                old = temp;
            if(i == newPos+1)
                new = temp;
            temp = temp->next;
        }
    }
    else if(oldPos > newPos)
    {
        for(int i = 0; i<totalNode; i++)
        {
            if(i == oldPos)
                old = temp;
            if(i == newPos)
                new = temp;
            temp = temp->next;
        }
    }

    old->prev->next = old->next;
    old->next->prev = old->prev;

    old->next = new;
    old->prev = new->prev;
    new->prev->next = old;
    new->prev = old;

    deleteNode(1);
    deleteNode(totalNode);
}

int insertNode(int position, int data)
{
    if(position < 1 || position > totalNode + 1)
    {
        return -1;
    }

    totalNode++;

    node *newNode = getNode(data);
    node *temp = Head;

    if(position == 1)
    {
        if(Head == NULL)
        {
            Head = newNode;
        }
        else
        {
            newNode->next = temp;
            temp->prev = newNode;
            Head = newNode;
        }
    }
    else if(position == totalNode)
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        newNode->prev = temp;
        temp->next = newNode;
    }
    else
    {
        for(int i = 1; i<position-1; i++)
        {
            temp = temp->next;
        }
        node *nextNode = temp->next;

        newNode->next = nextNode;
        newNode->prev = temp;
        nextNode->prev = newNode;
        temp->next = newNode;
    }

    return 1;
}

void freeList(void)
{
    while(Head != NULL)
    {
        node *temp = Head;
        Head = Head->next;
        free(temp);
    }
}