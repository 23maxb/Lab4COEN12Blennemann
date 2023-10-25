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

void destroyList(LIST* lp) {
    assert(lp != NULL);
    Node* pDel = lp->head->next;
    while (pDel->data != NULL) {
        pDel = pDel->next;
        free(pDel->prev);
    }
    free(pDel);
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
 *
 *
 * @param lp
 * @param item
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

void* getFirst(LIST* lp) {
    assert(lp != NULL);
    return lp->head->next->data;
}

void* getLast(LIST* lp) {
    assert(lp != NULL);
    return lp->head->prev->data;
}

void removeItem(LIST* lp, void* item) {
    assert(lp != NULL);
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

void* findItem(LIST* lp, void* item) {
    assert(lp != NULL);
    assert(item != NULL);
    Node* pDel = lp->head->next;
    while (pDel != lp->head) {
        if (lp->compare(pDel->data, item) == 0) {
            return pDel->data;
        }
        pDel = pDel->next;
    }
    return NULL;
}

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

void debugPrint(LIST* lp) {
    Node* a = lp->head->next;
    while (a != NULL && a->data != NULL) {
        printf("%d\n", *(int*) a->data);
        a = a->next;
    }
}