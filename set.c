//table.c
/**
 * This file (table.c) is an implementation for the set data type.
 * Multiple similar file exists (unsorted.c, sorted.c, and strings/table.c) that implements this set in various other ways.
 * The set data type guarantees no duplicate elements.
 * This implementation reduces the time complexity of searches for values by hashing.
 *
 * @author Max Blennemann
 * @version 10/10/23
 */

#include "set.h"
#include "list.c"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct set {
    LinkedList* data;
    unsigned int count; // Number of elements that contain data
    unsigned int size; // How much space is allocated to the array

    int (* compare)(); //Method passed in from createSet that compares two elements

    unsigned (* hash)(); //Method passed in from createSet that hashes an element
} genericCollisionProofSet;

/**
 * Returns a new set with the specified number of elements as the maximum capacity.
 *
 * @param maxElts the maximum amount of elements the set can hold
 * @return the newly allocated set
 * @timeComplexity O(N) Where N is the maximum number of elements the set can hold (maxElts)
 */
SET* createSet(int maxElts, int (* compare)(), unsigned (* hash)()) {
    assert(compare != NULL);
    assert(hash != NULL);
    assert(maxElts >= 0);
    genericCollisionProofSet* a = malloc(sizeof(genericCollisionProofSet));
    a->size = maxElts;
    a->count = 0;
    a->data = malloc(sizeof(LinkedList) * maxElts);
    assert(a->data != NULL);
    unsigned i = 0;
    for (; i < maxElts; i++) {
        a->data[i] = *createList(compare);
    }
    return a;
}

/**
 * Frees the memory allocated to the set.
 *
 * @param sp the set to destroy
 * @timeComplexity O(1)
 */
void destroySet(SET* sp) {
    assert(sp != NULL);
    unsigned i = 0;
    for (; i < sp->size; i++)
        destroyList(&sp->data[i]);
    free(sp);
}

/**
 * Returns the number of elements in the set
 *
 * @param sp the set to access
 * @return the number of unique elements
 * @timeComplexity O(1)
 */
int numElements(SET* sp) {
    assert(sp != NULL);
    return sp->count;
}

/**
 * Adds a new element to the set
 * Sorts the list after the element is added to guarantee the set is sorted
 *
 * @param sp the set to add an element to
 * @param elt the element to add.
 * @timeComplexity (O(N) + user given hash function) worst case; (O(1) + user given hash function) average case
 */
void addElement(SET* sp, void* elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    assert(sp->count < sp->size);
    unsigned index = sp->hash(elt) % sp->size;
    addFirst(&sp->data[index], elt);
    sp->count++;
}

/**
 * This method removes an element from the give set.
 * Marks the flag array for removed elements as 2.
 * This function will silently fail if the element given does not exist.
 *
 * @param sp the set to remove the element from
 * @param elt the element to remove
 * @timeComplexity (O(N) + user given hash function) worst case; (O(1) + user given hash function) average case
 */
void removeElement(SET* sp, void* elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    removeItem(&(sp->data[sp->hash(elt) % sp->size]), elt);
}


/**
 * Finds the element in the set.
 * Returns NULL if the element does not exist within the set.
 *
 * @precondition Set is sorted.
 * @param sp the set to search through
 * @param elt the element to search for
 * @return a pointer to the generic in the set if it exists
 * otherwise NULL
 * @timeComplexity O(N) worst case; O(1) average case
 */
void* findElement(SET* sp, void* elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    return findItem(&sp->data[sp->hash(elt) % sp->size], elt);
}

/**
 * Copies all the values in the set to a new array and returns that new array.
 * The user must free the array of generics before exiting to avoid a memory leak.
 * Since this set is not sorted by any distinguishable features of the generics
 * the returned array is not guaranteed to be sorted in any way.
 *
 * @param sp The set to access
 * @return A new array of void* pointers to the generics in the sets
 * @timeComplexity O(N)
 */
void* getElements(SET* sp) {
    assert(sp != NULL);
    void** toReturn = malloc(sp->count * sizeof(void*));
    assert(toReturn != NULL);
    unsigned i = 0;
    for (; i < sp->count; i++) {
        Node temp = *sp->data[i].head->next;
        while (temp.data != NULL) {
            toReturn[i] = temp.data;
            temp = *temp.next;
        }
    }
    return toReturn;
}