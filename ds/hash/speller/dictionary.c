// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//const unsigned int N = 9000;
#define N 10000

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int i, len = strlen(word);
    char* word1 = malloc(sizeof(char)*(len + 1));
    for(i = 0; i<len; i++)
    {
        word1[i] = tolower(word[i]);
    }
    word1[i] = '\0';

    int index = hash(word1);
    node* temp = table[index];
    while(temp)
    {
        if(!strcmp(word1, temp->word))
        {
            free(word1);
            return true;
        } 
        temp = temp->next;
    }
    free(word1);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

void setNull(void)
{
    for(int i = 0; i<N; i++)
    {
        table[i] = NULL;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    setNull(); //sets elements of the table to NULL
    FILE* file = fopen(dictionary, "r");
    if(!file) return false;

    char* word = malloc(sizeof(char)*(LENGTH + 1));
    while(fscanf(file, "%s", word) != EOF)
    {
        node* new = malloc(sizeof(node)*1);
        if(!new) return false;

        new->next = NULL;
        strcpy(new->word, word);
        int index = hash(word);

        if(table[index]) new->next = table[index];
        table[index] = new;
    }
    free(word);
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int totalNodes = 0;
    for(int i = 0; i<N; i++)
    {
        node* temp = table[i];
        while(temp)
        {
            totalNodes++;
            temp = temp->next;
        }
    }
    return totalNodes;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int deletedNodes = 0;
    int totalNodes = size();
    for(int i = 0; i<N; i++)
    {
        while(table[i])
        {
            node* temp = table[i];
            table[i] = table[i]->next;
            free(temp);
            deletedNodes++;
        }
    }
    if(deletedNodes != totalNodes)
    {
        printf("Error!\ntotal: %d\t\tdeleted: %d\n", totalNodes, deletedNodes);
        return false;
    }
    return true;
}
