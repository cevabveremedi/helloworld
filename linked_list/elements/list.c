/*
user can;
    -keep adding elements to a linked list (while choosing the position)
    -remove elements (by position)
    -invert the linked list
    -change the position of elements.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    
}node;

node * createList(node *head);
void displayList(node *head);
node * invertList(node **head);
node * rmFromList(node *head, int max);
node * change_element(node *head, int max);


int main(void)
{
    node *HEAD = NULL;
    int counter = 0;
    int removed = 0;
    int inverter = 0;
    int pos = 0;

    int loop = 1;
    printf("Type 'a' to add an element\tType 'r' to remove an element\n");
    printf("Type 'i' to invert the list\tType 'c' to change the position of an element\n");
    printf("Type 'd' to display the list\tType 'e' to exit.\n\nCommand: ");

    while(loop == 1)
    {
        int c = getchar();

        switch (c)
        {
            case '\n':
                break;
            case EOF:
            {
                loop = 0;
                printf("\tinput reception stopped\n");
                break;
            }
            case 'a':
            {
                HEAD = createList(HEAD);
                if(HEAD == NULL)
                {
                    printf("Memory error!\n");
                    return 1;
                }
                counter++;
                break;
            }
            case 'r':
            {
                printf("\nCurrent List:");
                displayList(HEAD);
                HEAD = rmFromList(HEAD, counter-removed);
                removed++;
                break;
            }     
            case 'i':
            {
                inverter++;
                HEAD = invertList(&HEAD);
                break;
            }
            case 'c':
            {
                pos++;
                printf("\nCurrent List:");
                displayList(HEAD);
                HEAD = change_element(HEAD, counter-removed);
                break;
            }
            case 'd':
            {
                displayList(HEAD);
                printf("\nCommand: ");
                break;
            }
            case 'e': 
            {
                loop = 0;
                break;
            }     
            default:
            {
                printf("It's not valid command!\na: add\nr: remove\ni: invert\nc: change\nd: display\ne: exit\n");
                printf("\nCommand: ");
                break;
            }
        }
    }
    printf("Report:\n");
    printf("%d nodes added.\n%d nodes removed.\n", counter, removed);
    printf("Total number of nodes atm: %d\n", counter-removed);
    printf("\nList has inverted %d times.\n", inverter);
    printf("Element position has changed %d times.\n", pos);

    while(HEAD != NULL)
    {
        node *temp = HEAD->next;
        free(HEAD);
        HEAD = temp;
    }

    return 0;
}

node * createList(node *head)
{
    node *p = NULL;
    node *temp = malloc(sizeof(node));

    printf("  Enter the data of the Node: ");
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
    printf("Element added to the list!\nCommand: ");
    return head;
}


void displayList(node *head)
{
    node *p = head;
    int i = 1;
    
    printf("\n");

    while(p != NULL)
    {
        printf("(%i) %d->   ", i, p->data);
        p = p->next;
        i++;
    }
    printf("NULL\n\n");
}

node * invertList(node **head) // TODO
{
    node *prev = NULL;
    node *curr = *head;
    node *next;

    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;

    printf("List is reversed now!\nCommand: ");
    return *head;
}

node * rmFromList(node *head, int max)
{
    node *junk = NULL;
    node *p = head;
    int rm;
    do
    {
    printf("Which element to remove: ");
    scanf("%d", &rm);
    }while(rm > max || rm < 0);

    if(rm == 1)
    {
        printf("\n%i\n", head->data);
        junk = head;
        head = head->next;
        free(junk);
        printf("Element removed from the list!\nCommand: ");
        return head;
    }

    for(int i = 1; i<rm-1; i++)
    {
        p = p->next;
    }
    node *prev_element = p;
    node *current = p->next;
    junk = current;
    node *next_element = current->next;

    printf("\n%i\n", current->data);
    prev_element->next = next_element;

    free(junk);
    printf("Element removed from the list!\nCommand: ");
    return head;
}

node * change_element(node *head, int max)
{
    node *p = head;
    node *k = head;
    node *temp = NULL;
    int element = -1, position = -1;

    do
    {
        printf("Enter element number and destination: ");
        scanf("%d%d", &element, &position);
        if(element == -1 || position == -1)
            return head;
    } while (element>max || element<=0 || position>max || position<=0 || element == position);

    if(element == 1)
    {
        temp = head;
        head = temp->next;
    }
    else
    {
        for(int i = 1; i<element; i++)
        {
            p = p->next;
        }
        temp = p;

        while(k->next != p)
        {
            k = k->next;
        }
        k->next = p->next;
    }

    p = head;
    k = head;

    if(position == 1)
    {
        temp->next = head;
        head = temp;
    }
    else
    {
        for(int j = 1; j<position-1; j++)
        {
            p = p->next;
        }
        node *prePos = p;
        node *pos = prePos->next;

        temp->next = pos;
        prePos->next = temp;
    }
    printf("Element position changed!\n Command: ");
    return head;
}