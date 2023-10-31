
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.c"
#include <assert.h>

# define MAX_SIZE 18000

static unsigned strhash(int s) {
    return s;
}

static int s(int a, int b) {
    return a - b;
}

int main(int argc, char* argv[]) {
    SET* unique = createSet(100, s, strhash);
    int b = 0;
    int* p = 0;
    for (b = 0; b < 2; b++) {
        p = malloc(sizeof(int));
        assert(p != NULL);
        *p = b;
        printf("adding %u\n", *(int*) p);
        addElement(unique, p);
    }

    printf("\ntotal Count: %u", numElements(unique));
    destroySet(unique);
    exit(EXIT_SUCCESS);
}
