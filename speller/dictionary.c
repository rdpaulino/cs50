// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
const unsigned int N = 10000;

// declaring file
FILE *file = NULL;

// declaring word counter
int words = 0;

// Hash table
node *table[N];

//declaring hashIndex
int hashIndex;

//declaring lower case version of word
char lowerCaseWord[LENGTH + 1];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    hashIndex = hash(word);
    node *cursor = table[hashIndex];
    //int wordMatch;

    while (cursor != NULL)
    {
        //wordMatch = strcasecmp(word, cursor->word);

        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        lowerCaseWord[i] = tolower(word[i]);
    }

    //https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
    unsigned int hashValue = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hashValue = (hashValue << 2)^lowerCaseWord[i];
        //printf("HASH RETURNED: %i\n", hashval);
    }

    hashValue = hashValue % N;
    //printf("HASH RETURNED: %i\n", hashValue);
    return hashValue;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    file = fopen(dictionary, "r");

    // Check if file opened successfully
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        words++;

        node *n = malloc(sizeof(node));
        n->next = NULL;

        if (n != NULL)
        {
            hashIndex = hash(word);

            strcpy(n->word, word);
            //printf("word copied: %s\n", word);

            // TODO insert word to linked list in hash table
            //if no node exists
            if (table[hashIndex] == NULL)
            {
                table[hashIndex] = n;
            }
            //if node exists, append node at the beginning
            else
            {
                n->next = table[hashIndex];
                table[hashIndex] = n;
            }
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    // Check if file opened successfully
    if (file == NULL)
    {
        return 0;
    }
    else
    {
        // Print file statistics
        //printf("\n");
        //printf("Total words = %i\n", words);
        return words;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = NULL;
    node *tmp = NULL;

    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            cursor = table[i];

            while (cursor != NULL)
            {
                tmp = cursor;
                cursor = cursor->next;
                free(tmp);
            }
        }
    }

    return true;
}
