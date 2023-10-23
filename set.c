//set.c
/**
 * This file (table.c) is an implementation for the set data type.
 * Multiple similar file exists (unsorted.c, sorted.c, and generic/table.c) that implements this set in various other ways.
 * The set data type guarantees no duplicate elements.
 * This implementation reduces the time complexity of searches for values by hashing .
 * However, this implementation leads to a O(N) worst case scenario time complexity for the addElement function.
 *
 * @author Max Blennemann
 * @version 10/10/23
 */

#include "set.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "stdbool.h"

typedef struct node {
    void* data;
    struct node* next;
    struct node* prev;
} Node;

typedef struct list {
    int count;
    struct node* head;

    int (* compare)();
} LinkedList;

