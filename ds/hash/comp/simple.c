
/**
 * This stupid program compares two method. There is a linked list array of size 10
 * and a regular old linked list. Both stores 1 to 999,999 but linked list array 
 * stores 100,000 nodes each while regular list stores all of them.
 * At the end of the day, we'll see how many steps we gain by using linked list array.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int val;
    struct node* next;
}node;

node* insert(node* head, int data);
int hash_function(int data);
int find_node(node* head, int data);

int main(void)
{
    node** hash_table = malloc(sizeof(node*)*10);
    node* head = NULL;

    for(int i = 999999; i>0; i--)
    {
        int n = hash_function(i);
        hash_table[n] = insert(hash_table[n], i);
        head = insert(head, i);
    }

    int x = 999999;
    printf("for %d: diff: %d\n", x, find_node(head, x) - find_node(hash_table[9], x));
    x = 100;
    printf("for %d: diff: %d\n", x, find_node(head, x) - find_node(hash_table[0], x));
    x = 100001;
    printf("for %d: diff: %d\n", x, find_node(head, x) - find_node(hash_table[1], x));

    for(int i = 0; i<10; i++)
    {
        while(hash_table[i])
        {
            node* temp = hash_table[i];
            hash_table[i] = hash_table[i]->next;
            free(temp);
            temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(hash_table);
}

node* insert(node* head, int data)
{
    node* temp = malloc(sizeof(node)*1);
    temp->val = data;
    temp->next = head;
    return temp;
}

int hash_function(int data)
{
    return data/100000;
}

int find_node(node* head, int data)
{
    int count = 0;
    while(head)
    {
        if(head->val == data)
        {
            break;
        }
        count++;
        head = head->next;
    }
    return count;
}