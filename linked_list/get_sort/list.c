/*
creates a "n" sized of linked list, gets the input, sorts the data, displays the list.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

node * CreateLinkedList(int n);
node * SortLinkedList(node *head, int n);
void DisplayList(node *head);

int main(void)
{
    node *HEAD = NULL;

    int n;
    printf("Enter how many Nodes do you want: ");
    scanf("%d", &n);

    HEAD = CreateLinkedList(n);

    SortLinkedList(HEAD, n);
    DisplayList(HEAD);

    while(HEAD != NULL)
    {
        node *temp = HEAD->next;
        free(HEAD);
        HEAD = temp;
    }
}

node * CreateLinkedList(int n)
{
    int i;

    node *head = NULL;
    node *temp = NULL;
    node *p = NULL;

    for(i = 0; i < n; i++)
    {
        temp = malloc(sizeof(node));
        if(temp == NULL)
        {
            printf("No Memory!\n");
            exit(0);
        }

        printf("\nEnter the data of Node %d: ", i+1);
        scanf("%d", &(temp->data));
        temp->next = NULL;
        
        if(head == NULL)
        {
            head = temp;
        }
        else
        {
            p = head;
            while(p->next != NULL)
            {
                p = p->next;
            }
            p->next = temp;
        }
    }
    return head;
}

void DisplayList(node *head)
{
    node *p = head;
    
    printf("\n");

    while(p != NULL)
    {
        printf("%d->  ", p->data);
        p = p->next;
    }
    printf("NULL\n\n");
}

node * SortLinkedList(node *head, int n)
{
    for(int i = 0; i<n; i++)
    {
        node *p = head;
        while(p->next != NULL)
        {
            if(p->data > p->next->data)
            {
                if(p->next == NULL)
                {
                    break;
                }
                int temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;
            }
            p = p->next;
        }
    }
    return head;
}