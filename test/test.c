#include <stdio.h>
#include <assert.h>
#include "../src/core.h"

int main() {
    int* mynum = calloc(1, sizeof(int));
    printf("%p: %d\n", mynum, *mynum);
    *mynum = 15;

    while (*mynum > 0) {
        (*mynum)--;
        printf("\t%d\n", *mynum);
    }

    free(mynum);
    return 0;
}
