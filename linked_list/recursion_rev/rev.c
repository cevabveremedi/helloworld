/**
 * This Program creates a linked list:
 * 35 - 30 - 25 - 20 - 15 - 10 - 5
 * then reverse the list using recursion.
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

node* recursiveRev(node* first);
node * createList(node *head, int number);
void printList(node * head);
void freeList(node * head);

int main(void)
{
    node *HEAD = NULL;

    HEAD = createList(HEAD, 5);
    HEAD = createList(HEAD, 10);
    HEAD = createList(HEAD, 15);
    HEAD = createList(HEAD, 20);
    HEAD = createList(HEAD, 25);
    HEAD = createList(HEAD, 30);        
    HEAD = createList(HEAD, 35);
    
    printf("Original: ");
    printList(HEAD);

    HEAD = recursiveRev(HEAD);
    printf("Reversed: ");
    printList(HEAD);

    freeList(HEAD);
    return 0;
}

node * createList(node *head, int number)
{
    node *temp = (node *) malloc(sizeof(node));
    temp->data = number;

    if(head == NULL)
    {
        temp->next = NULL;
        return temp;
    }
    
    temp->next = head;
    head = temp;
    return head;
}

void printList(node *head)
{
    while(head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

node* recursiveRev(node *first)
{
    if(first == NULL) // list does not exist.
    {
        return NULL; 
    }

    if(first->next == NULL) // list with only one node.
    {
        return first; 
    }
        
    node* rest = recursiveRev(first->next); // recursive call on rest.

    first->next->next = first; // make first; link to the last node in the reversed rest.

    first->next = NULL; // since first is the new last, make its link NULL.

    return rest; // rest now points to the head of the reversed list.
}

void freeList(node *head)
{
    while(head != NULL)
    {
        node * temp = head;
        head = head->next;
        free(temp);
    }
}