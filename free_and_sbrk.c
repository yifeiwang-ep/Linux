#include <stdio.h>
#include <stdlib.h>
#define MAX_ALLOCS 1000000

int main(int argc, char *argv[]){
    char *ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;
    printf("\n");

    numAllocs = GetInt(argv[1], GN_GT_O, "num-allocs");
    blockSize = GetInt(argv[2], GN_GT_O | GN_ANY_BASE, "block-size");

    freeStep = (argc > 3) ? GetInt(argv[3], GN_GT_O, "step") : 1;
    freeMin = (argc > 4) ? GetInt(argv[4], GN_GT_O, "min") : 1;
    freeMax = (argc > 5) ? GetInt(argv[5], GN_GT_O, "mac") : numAllocs;

    printf("Initial program break:    %10p\n", sbrk(0));

    printf("Allocating %d*%d bytes\n", numAllocs, blockSize);
    for(j = 0; j < numAllocs; j++){
        ptr[j] = malloc(blockSize);
        if(ptr[j] == NULL){
            exit(1);
        }
    }

    printf("Program break is now:    %10p\n", sbrk(0));
    printf("Freeing blocks from %d to %d in steps of %d\n", freeMin, freeMax, freeStep);
    for(j = freeMin - 1; j < freeMax; j += freeStep){
        free(ptr[j]);
    }

    printf("After free(), program break is:    %10p\n", sbrk(0));

    return 0;
}
