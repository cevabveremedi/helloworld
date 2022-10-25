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
void clearInputBuffer(void);
void printHelp(void);

int main(void)
{
    node *HEAD = NULL;
    int counter, removed, inverter, pos, loop;
    counter = removed = inverter = pos = 0;
    loop = 1;

    // input buffer issue is still a problem. Don't forget to fix it later!

    while(loop)
    {
        printf("\nType 'h' to help!\nCommand: ");

        //int c = getchar();
        //clearInputBuffer();

        char options[] = {'a', 'A', 'r', 'R', 'i', 'I', 'c', 'C', 'd', 'D', 'e', 'E', 'h', 'H'};
        int arraySize = sizeof(options) / sizeof(options[0]);

        char c;
        while(1)
        {
            int valid = 0;
            scanf("%c", &c);

            for(int i = 0; i < arraySize; i++)
            {
                if(c == options[i])
                {
                    valid = 1;
                    break;
                }
            }

            if(valid)
                break;
        }

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
            case 'h':
            case 'H':
            {
                printHelp();
                break;
            }
            case 'a':
            case 'A':
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
            case 'R':
            {
                printf("\nCurrent List:");
                displayList(HEAD);
                HEAD = rmFromList(HEAD, counter-removed);
                removed++;
                break;
            }     
            case 'i':
            case 'I':
            {
                inverter++;
                HEAD = invertList(&HEAD);
                break;
            }
            case 'c':
            case 'C':
            {
                pos++;
                printf("\nCurrent List:");
                displayList(HEAD);
                HEAD = change_element(HEAD, counter-removed);
                break;
            }
            case 'd':
            case 'D':
            {
                displayList(HEAD);
                break;
            }
            case 'e':
            case 'E': 
            {
                loop = 0;
                break;
            }     
            default:
            {
                printf("It's not a valid command!");
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

void printHelp(void)
{
    printf("\n");
    printf("Type 'a' to add an element.\tType 'r' to remove an element.\n");
    printf("Type 'i' to invert the list.\tType 'c' to change the position of an element.\n");
    printf("Type 'd' to display the list.\tType 'e' to exit.\n\n");
}

void clearInputBuffer(void)
{
    // getchar input buffer
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

node * createList(node *head)
{
    node *p = NULL;
    node *temp = malloc(sizeof(node));
    temp->next = NULL;

    printf("  Enter the data of the Node: ");
    
    // scanf causes an infinite loop if the input type is wrong; this is a workaround
    while(!scanf("%d", &(temp->data)))
    {
        scanf("%*[^\n]"); //discard that line up to the newline
        printf("Could not read an integer value!\n");
        printf("  Enter the data of the Node: ");
    }
    
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
    printf("\n\tElement added to the list!\n");
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

    printf("\n\tList is reversed now!\n");
    return *head;
}

node * rmFromList(node *head, int max)
{
    node *junk = NULL;
    node *p = head;
    int rm;

    /*
    do
    {
        printf("Which element to remove: ");
        scanf("%d", &rm);
    }while(rm > max || rm <= 0);
    */

    // scanf causes an infinite loop if the input type is wrong; this is a workaround
    while(1)
    {
        printf("Which element do you want to remove: ");
        while(!scanf("%d", &rm))
        {
            scanf("%*[^\n]"); //discard that line up to the newline
            printf("Could not read an integer value!\n");
            printf("Which element do you want to remove: ");
        }
        if(rm > max || rm <= 0)
        {
            printf("Invalid option!\n");
        }
        else
        {
            break;
        }
    }

    if(rm == 1)
    {
        printf("\n%i\n", head->data);
        junk = head;
        head = head->next;
        free(junk);
    }
    else
    {
        for(int i = 1; i<rm-1; i++)
        {
            p = p->next;
        }
        node *prev_element = p;
        node *current = p->next;
        junk = current;
        node *next_element = current->next;
        printf("\n\t%i\n\t", current->data);
        prev_element->next = next_element;
        free(junk);
    }
    printf("Element removed from the list!\n");
    return head;
}

node * change_element(node *head, int max)
{
    if(max == 1)
    {
        printf("\n\tThere is only one element!\n");
        return head;
    }

    node *p = head;
    node *k = head;
    node *temp = NULL;
    int element = -1, position = -1;

    /*
    do
    {
        printf("Enter element number and destination: ");
        scanf("%d%d", &element, &position);
        if(element == -1 || position == -1)
            return head;
    } while (element>max || element<=0 || position>max || position<=0 || element == position);
    */

    while(1)
    {
        printf("Enter element number and destination: ");
        while(!scanf("%d%d", &element, &position))
        {
            scanf("%*[^\n]"); //discard that line up to the newline
            printf("Could not read an integer value!\n");
            printf("Enter element number and destination: ");
        }
        if(element>max || element<=0 || position>max || position<=0 || element == position)
        {
            printf("Invalid option!\n");
        }
        else
        {
            break;
        }
    }

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
    printf("\n\tElement position changed!\n");
    return head;
}