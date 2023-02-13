#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "cslice.h"
#include "optionalInt.h"

// This is a linkedlist to keep track of all of the functions and their key information: name, location, name and number of Params
typedef struct functionNode
{
    Slice key;
    struct functionNode *next;
    char const *location;
    Slice *params;
    uint64_t numParams;

} functionNode;

struct functionNode *functionHead; // global variable - pointer to head node.

// Creates a new Node and returns pointer to it.
struct functionNode *getNewFunctionNode(Slice k, char const *ptr, uint64_t v)
{
    struct functionNode *newNode = (struct functionNode *)malloc(sizeof(struct functionNode));
    newNode->key = k;
    newNode->next = NULL;
    newNode->location = ptr;
    newNode->numParams = v;
    newNode->params = (struct Slice *)malloc(sizeof(struct Slice) * v);
    return newNode;
}

// Inserts a Node at tail of linked list
void insertFunction(Slice k, char const *ptr, uint64_t v)
{

    if (functionHead == NULL)
    {
        struct functionNode *newNode = getNewFunctionNode(k, ptr, v);
        functionHead = newNode;
        return;
    }
    struct functionNode *temp = functionHead;
    while (temp != NULL)
    {
        if (temp->next == NULL)
            break;
        temp = temp->next;
    }
    struct functionNode *newNode = getNewFunctionNode(k, ptr, v);
    temp->next = newNode;
}

// Returns the value associated with a Slice in the LinkedList as an optionalInt
struct functionNode *findFunction(Slice k)
{
    struct functionNode *temp = functionHead;
    while (temp != NULL)
    {
        if (equalsSlice(k, temp->key))
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
