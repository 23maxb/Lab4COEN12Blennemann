//list.c
/**
 * This file (list.c) is an implementation for the list data type.
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

LIST* createList(int (* compare)()) {
    assert(compare != NULL);
    LinkedList* lp = malloc(sizeof(LinkedList));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = NULL;
    lp->compare = compare;
    return lp;
}

void destroyList(LIST* lp) {
    assert(lp != NULL);
    Node* pDel = lp->head;
    Node* pNext;
    while (pDel != NULL) {
        pNext = pDel->next;
        free(pDel);
        pDel = pNext;
    }
    free(lp);
}

int numItems(LIST* lp) {
    assert (lp != NULL);
    return lp->count;
}

/**
 *
 *
 * @param lp
 * @param item
 */
void addFirst(LIST* lp, void* item) {
    assert(lp != NULL);
    Node* pNew = malloc(sizeof(Node));
    assert(pNew != NULL);
    pNew->data = item;
    if (lp->head != NULL) {
        lp->head = pNew;
        pNew->prev = pNew;
        pNew->next = pNew;
    } else {
        pNew->next = lp->head;
        pNew->prev = lp->head->prev;
        lp->head = pNew;
    }
    lp->count++;
}

/**
 *
 *
 * @param lp
 * @param item
 */
void addLast(LIST* lp, void* item) {
    assert(lp != NULL);
    Node* pNew = malloc(sizeof(Node));
    assert(pNew != NULL);
    pNew->data = item;
    pNew->next = lp->head;
    pNew->prev = lp->head->prev;
    lp->head->prev = pNew;
    pNew->prev->next = pNew;
    lp->count++;
}

void* removeFirst(LIST* lp)
{
    assert(lp != NULL);
    assert(lp->count > 0);
    Node* pDel = lp->head;
    void* toReturn = pDel->data;
    if (lp->count == 1) {
        lp->head = NULL;
    } else {
        lp->head = pDel->next;
        lp->head->prev = pDel->prev;
        lp->head->prev->next = lp->head;
    }
    free(pDel);
    lp->count--;
    return toReturn;
}

void* removeLast(LIST* lp);

void* getFirst(LIST* lp);

void* getLast(LIST* lp);

void removeItem(LIST* lp, void* item);

void* findItem(LIST* lp, void* item);

void* getItems(LIST* lp);