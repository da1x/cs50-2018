// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node *nodeClass;

//Create node
typedef struct node
{
    bool is_word;
    struct node *children[27];
} node;

//The root node
node *root;

nodeClass createNode(void)
{
    nodeClass node = malloc(sizeof(struct node));
    if (node == NULL)
    {
        return NULL;
    }

    node->is_word = false;

    for (int i = 0; i < 27; i++)
    {
        node->children[i] = NULL;
    }

    return node;
}

//Declare bool function for later use
void FreeNode(node *ptr);

//Total number of nodes
int totalNodes;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //TODO:
    //For each letter of the word, go to corresponding element in the children
    //if NULL then the word is misspelled
    //if not NULL then move deeper down the trie
    //once it is the end of the word we need to check if the bool is_word is true or not

    //Make another node as the cursor with same location as root
    node *cursor = root;

    //Find the index for the charactar by using ASCII value
    int id = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == '\'')
        {
            id = 26;
        }
        else
        {
            id = toupper(word[i]) % 'A';
        }

        //Check if the children its NULL or not
        if (cursor->children[id] != NULL)
        {
            //if node exit then go deeper into the trie
            cursor = cursor->children[id];
        }
        else
        {
            //if NULL then node is not created, this also means dictionary doesnt have the word
            //Meaning its misspelled.
            return false;
        }
    }

    //Once we hit the last would we would need to check and return the bool of is_word
    if (cursor->is_word == true)
    {
        return true; //if true then word exist, else is misspelled/doesnt exist.
    }
    else
    {
        return false;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Malloc memory for root
    root = createNode();

    //Keep track of number of nodes
    totalNodes = 0;

    //Read dictionary and check if the dictionary is null or not
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        //Unload dictionary if it cant be open
        fprintf(stderr, "%s could not be open.\n", dictionary);
        unload();
        return false;
    }

    //Make another node as the cursor with same location as root
    node *cursor = root;

    //Read each character in the dictionary
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) //Check if the c is EOF (-1)
    {
        if (c == '\n')
        {
            //Mark as word when we hit the \n aka new line
            cursor->is_word = true;

            //Increment node counter by 1
            totalNodes++;

            //Reset the cursor pointer back to the root pointer of the trie
            cursor = root;
        }
        else
        {
            //Find the index for the charactar by using ASCII value
            int id = 0;

            if (c == '\'')
            {
                id = 26;
            }
            else
            {
                id = toupper(c) % 'A';
            }

            //Check if node is already made
            if (cursor->children[id] == NULL)
            {
                //Make a new node and malloc the memory
                cursor->children[id] = createNode();
            }

            //if exist then we will keep go deeper into the trie
            cursor = cursor->children[id];
        }
    }

    //Close the dictionary
    fclose(fp);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalNodes;
}

void FreeNode(node *ptr)
{
    //Check if children node is free, if not then free it
    for (int i = 0; i < 27; i++)
    {
        if (ptr->children[i] != NULL)
        {
            FreeNode(ptr->children[i]);
        }
    }

    //Free parent node once children are all free-ed
    free(ptr);

    return;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // Unload from botton to up
    // Travel to lowest possible node, free all pointers in children
    // Freeing all element until you hit root node
    node *currentnode = root;
    FreeNode(currentnode);
    return true;
}
