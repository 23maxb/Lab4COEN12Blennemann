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
    int i = 51;
    printf("adding %u\n", i);
    addLast(lp, &i);
    i = 5;
    printf("adding %u\n", i);
    addLast(lp, &i);
    i = 7;
    printf("adding %u\n", i);
    addLast(lp, &i);
    i = 17;
    printf("adding %u\n", i);
    addLast(lp, &i);
    i = 99;
    printf("adding %u\n", i);
    addLast(lp, &i);
    printf("numItems: %d\n", numItems(lp));
    printf("first: %d\n", *(int*) getFirst(lp));
    printf("last: %d\n", *(int*) getLast(lp));
    printf("numItems: %d\n", numItems(lp));
    debugPrint(lp);

    destroyList(lp);
    exit(EXIT_SUCCESS);
}