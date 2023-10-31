# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
#include "set.c"

int compare(int a, int b) {
    return a - b;
}

int main(int argv, char* argc[]) {
    LIST* lp = createList(strcmp);
    addFirst(lp, "hi");
    addFirst(lp, "yea");
    addFirst(lp, "dfak");
    addFirst(lp, "dfak");
    addFirst(lp, "dfak");
    addFirst(lp, "yellow");
    addFirst(lp, "dfak");


    printf("\nnumItems: %d\n", numItems(lp));
    printf("first: %s\n", getFirst(lp));
    removeFirst(lp);
    printf("first: %s\n", getFirst(lp));
    printf("last: %s", getLast(lp));
    removeLast(lp);
    removeLast(lp);
    printf("\nlast: %s", getLast(lp));
    removeItem(lp, "yellow");
    printf("\nremoving yellow");
    removeItem(lp, "yellow");
    printf("\nnumItems: %d\n", numItems(lp));
    destroyList(lp);
    exit(EXIT_SUCCESS);
}