// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 27;

// Hash table
node *table[N];

//Dictionary size
int dict_size = 0;
int i = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int check_index = hash(word);
    node *current_node = table[check_index];
    
    while (current_node != NULL)
    {

        if (strcasecmp(current_node->word, word) == 0)
        {
            //We have found the word!
            return true;
        }
        
        //We could not find the word.
        current_node = current_node->next;
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    //This hash function returns the index that the word is going to be stored considering the first letter of the word
    //First check if the first letter of the word is upper case alphabetic character
    if (word[0] <= 90 && word[0] >= 65)
    {
        return (word[0] - 65);
    }
    //Check if the first letter of the word is a lower case alphabetic character
    else if (word[0] <= 122 && word[0] >= 97)
    {
        return (word[0] - 97);
    }
    else
    {
        return 26;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");

    if (f == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];

    while (fscanf(f, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }
        
        //Copy the word to the node and set next node pointer of node n to NULL
        strcpy(n->word, word);
        n->next = NULL;
                
        //get the index value (where to store the word in table) from hash function
        i = hash(n->word);

        //if the ith element of the table is empty
        if (table[i] == NULL)
        {
            table[i] = n;
        }
        else
        {
            n->next = table[i];
            table[i] = n;
        }
        dict_size++;
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Iterate over all of the indexes in hash table
    for (int j = 0; j < N; j++)
    {
        node *head = table[j];
        node *cursor = head;
        node *tmp = head;
        
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
