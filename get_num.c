#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "get_num.h"
#include <limits.h>


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
