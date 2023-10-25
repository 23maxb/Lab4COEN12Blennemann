//list.c
/**
 * This file (list.c) is an implementation for the list data type.
 * It uses an arraylist to model the list internally.
 *
 * @author Max Blennemann
 * @version 10/23/23
 */

#include "list.h"
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
    unsigned count;
    Node* head;

    int (* compare)();
} LinkedList;

/**
 * Creates an empty list with a single dummy node (data = NULL)
 *
 * @param compare method containing the way to compare values
 * @return the list created
 * @timeComplexity O(1)
 */
LIST* createList(int (* compare)()) {
    LinkedList* lp = malloc(sizeof(LinkedList));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = malloc(sizeof(Node));
    assert(lp->head != NULL);
    lp->head->data = NULL;
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    lp->compare = compare;
    return lp;
}

/**
 * Frees the memory allocated to the list.
 *
 * @param lp the list to destroy
 * @timeComplexity O(N)
 */
void destroyList(LIST* lp) {
    assert(lp != NULL);
    Node* pDel = lp->head->next;
    while (pDel->data != NULL) {
        pDel = pDel->next;
        free(pDel->prev);
    }
    //after exiting this loop pDel->data == NULL
    free(pDel);
    free(lp);
}

/**
 * Returns the number of elements in the list
 * same as just accessing lp->count directly
 *
 * @param lp the list to access
 * @return the number of elements
 * @timeComplexity O(1)
 */
int numItems(LIST* lp) {
    assert (lp != NULL);
    return lp->count;
}

/**
 * Adds an element to the start of the list.
 * Remember this is a reference so if a variable is added in a for loop only the final value will be stored multiple
 * times.
 *
 * @param lp the list to edit
 * @param item the item to add
 * @timeComplexity O(1)
 */
void addFirst(LIST* lp, void* item) {
    assert(lp != NULL);
    assert(item != NULL);
    Node* pNew = malloc(sizeof(Node));
    assert(pNew != NULL);
    pNew->data = item;
    pNew->next = lp->head->next;
    pNew->prev = lp->head;
    lp->head->next->prev = pNew;
    lp->head->next = pNew;
    lp->count++;
}

/**
 * Adds an element to the end of the list.
 *
 * @param lp the list to edit
 * @param item the value to add
 * @timeCompleixty O(1)
 */
void addLast(LIST* lp, void* item) {
    assert(lp != NULL);
    assert(item != NULL);
    Node* pNew = malloc(sizeof(Node));
    assert(pNew != NULL);
    pNew->data = item;
    pNew->next = lp->head;
    pNew->prev = lp->head->prev;
    lp->head->prev->next = pNew;
    lp->head->prev = pNew;
    lp->count++;
}

/**
 * Removes the first element.
 *
 * @param lp
 * @return the data stored in the first node before removal (ie the removed value)
 * @timeComplexity O(1)
 */
void* removeFirst(LIST* lp) {
    assert(lp != NULL);
    if (lp->count == 0)
        return NULL;
    assert(lp->count > 0);
    Node* pDel = lp->head->next;
    void* toReturn = pDel->data;
    lp->head->next = lp->head->next->next;
    lp->head->next->prev = lp->head;
    free(pDel);
    lp->count--;
    return toReturn;
}
/**
 * Removes the last node in the list.
 *
 * @param lp the list to modify
 * @return the data stored in the last node before removal (ie the removed value)
 * @timeComplexity O(1)
 */
void* removeLast(LIST* lp) {
    assert(lp != NULL);
    if (lp->count == 0)
        return NULL;
    assert(lp->count > 0);
    Node* pDel = lp->head->prev;
    void* toReturn = pDel->data;
    lp->head->prev = lp->head->prev->prev;
    lp->head->prev->next = lp->head;
    free(pDel);
    lp->count--;
    return toReturn;
}

/**
 * Returns the first element in the list
 *
 * @param lp the list to access
 * @return the first element's value
 */
void* getFirst(LIST* lp) {
    assert(lp != NULL);
    return lp->head->next->data;
}

/**
 * Returns the last element in the list
 *
 * @param lp the list to access
 * @return the value stored in the last node
 */
void* getLast(LIST* lp) {
    assert(lp != NULL);
    return lp->head->prev->data;
}

/**
 * Removes the item from the list.
 * Can silently fail.
 * Only removes 1 item (the first occurrence of the value).
 *
 * @param lp the list to modify
 * @param item the value to remove
 * @timeComplexity O(N)
 */
void removeItem(LIST* lp, void* item) {
    assert(lp != NULL);
    assert(lp->compare != NULL);
    if (lp->count == 0)
        return;
    assert(item != NULL);
    Node* pDel = lp->head->next;
    while (pDel != lp->head) {
        if (lp->compare(pDel->data, item) == 0) {
            pDel->prev->next = pDel->next;
            pDel->next->prev = pDel->prev;
            free(pDel);
            lp->count--;
            return;
        }
        pDel = pDel->next;
    }
}

/**
 * Finds the item in the list and returns a reference to that value.
 *
 * @param lp the list to access
 * @param item the item to find
 * @return the reference to the value or NULL if the element doesn't exist
 * @timeComplexity O(N)
 */
void* findItem(LIST* lp, void* item) {
    assert(lp != NULL);
    assert(item != NULL);
    Node* pDel = lp->head->next;

    while (pDel != lp->head) {
        printf("hi");
        if (lp->compare(pDel->data, item) == 0) {
            return pDel->data;
        }
        pDel = pDel->next;
    }
    return NULL;
}

/**
 * Returns an array of void* pointers to the values in the list.
 *
 * @param lp the list to access
 * @return A list of values (sorted in the same order as in the list)
 * @timeComplexity O(N)
 */
void* getItems(LIST* lp) {
    assert(lp != NULL);
    void** items = malloc(sizeof(void*) * lp->count);
    assert(items != NULL);
    Node* pDel = lp->head->next;
    unsigned i = 0;
    while (pDel->data != NULL) {
        items[i] = pDel->data;
        pDel = pDel->next;
        i++;
    }
    return items;
}