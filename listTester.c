# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
#include "list.c"

int compare(int a, int b) {
    return a - b;
}

int main(int argv, char* argc[]) {
    LIST* lp = createList(NULL);
    int* p;
    int b;
    for (b = 0; b < 8; b++) {
        p = malloc(sizeof(int));
        assert(p != NULL);
        *p = b;
        printf("adding %u\n", *(int*) p);
        addLast(lp, p);
    }
    printf("numItems: %d\n", numItems(lp));
    printf("first: %d\n", *(int*) getFirst(lp));
    removeFirst(lp);
    printf("first: %d\n", *(int*) getFirst(lp));
    printf("last: %d\n", *(int*) getLast(lp));
    removeLast(lp);
    removeLast(lp);
    printf("last: %d\n", *(int*) getLast(lp));
    printf("numItems: %d\n", numItems(lp));
    destroyList(lp);
    exit(EXIT_SUCCESS);
}