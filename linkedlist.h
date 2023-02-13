#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "cslice.h"
#include "optionalInt.h"

// LinkedList Node
typedef struct Node
{
    Slice key;
    struct Node *next;
    uint64_t value;
} Node;

struct Node *head; // global variable - pointer to head node.

// Creates a new Node and returns pointer to it.
struct Node *getNewNode(Slice k, uint64_t v)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = k;
    newNode->value = v;
    newNode->next = NULL;
    return newNode;
}

// Inserts a Node at tail of linked list unless there is already a Node with the Slice
// If there is a Node it replaces the value of the Node
void insert(Slice k, uint64_t v)
{

    if (head == NULL)
    {
        struct Node *newNode = getNewNode(k, v);
        head = newNode;
        return;
    }
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (equalsSlice(k, temp->key))
        {
            temp->value = v;
            return;
        }
        if (temp->next == NULL)
            break;
        temp = temp->next;
    }
    struct Node *newNode = getNewNode(k, v);
    temp->next = newNode;
}

// Returns the value associated with a Slice in the LinkedList as an optionalInt
optionalInt find(Slice k)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (equalsSlice(k, temp->key))
        {
            optionalInt i1 = {true, temp->value};

            return i1;
        }
        temp = temp->next;
    }
    optionalInt i1 = {false, 0};
    return i1;
}
