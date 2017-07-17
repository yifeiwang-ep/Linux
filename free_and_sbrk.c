#include <stdio.h>
#include <stdlib.h>
#include "./get_num.h"
#include <limits.h>
#define MAX_ALLOCS 1000000

#define GN_GT_0 2
#define GN_ANY_BASE 0100
#define GN_BASE_8 0200
#define GN_BASE_16 0400
static long getNum(const char *fname, const char *arg, int flags, const char* name){
    long res;
    char *endptr;
    int base;
    if (arg == NULL || *arg == '\0'){
        printf("error getnum\n");
        return 0;
    }

    base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? :(flags & GN_BASE_16) ? 16 : 10;
    res = strtol(arg, &endptr, base);
    return res;
}

int getInt(const char *arg, int flags, const char *name){
    long res;
    res = getNum("getInt", arg, flags, name);
    if(res > INT_MAX || res < INT_MIN){
        printf("error getnum\n");
        return 0;
    }

    return (int)res;
}


int main(int argc, char *argv[]){
    char *ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;
    printf("\n");

    numAllocs = getInt(argv[1], GN_GT_0, "num-allocs");
    blockSize = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");

    freeStep = (argc > 3) ? getInt(argv[3], GN_GT_0, "step") : 1;
    freeMin = (argc > 4) ? getInt(argv[4], GN_GT_0, "min") : 1;
    freeMax = (argc > 5) ? getInt(argv[5], GN_GT_0, "mac") : numAllocs;

    printf("Initial program break:    %10p\n", sbrk(0));

    printf("Allocating %d*%d bytes\n", numAllocs, blockSize);
    for(j = 0; j < numAllocs; j++){
        ptr[j] = malloc(blockSize);
        if(ptr[j] == NULL){
            exit(1);
        }
    }

    printf("Program break is now:    %10d\n", sbrk(0));
    printf("Freeing blocks from %d to %d in steps of %d\n", freeMin, freeMax, freeStep);
    for(j = freeMin - 1; j < freeMax; j += freeStep){
        free(ptr[j]);
    }

    printf("After free(), program break is:    %10d\n", sbrk(0));

    return 0;
}
