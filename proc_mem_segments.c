#include <stdio.h>
#include <stdlib.h>

extern char etext, edate, end;

char globBuf[65535]; //bss
int primes[] = {2, 3, 5, 7}; //初始化数据段

static int square(int x){ //
    int result;

    result = x * x;
    return result;
}

static void doCal(int val){
    printf("the square of %d is %d\n", val, square(val));
    if(val < 1000){
        int t;
        t = val * val * val;
        printf("the cube of %d if %d\n", val, t);
    }
}

int main(int argc, char *argv[]){
    static int key = 9973;
    static char mbuf[10240000];
    char *p;
    p = malloc(1024);//heap segment
    doCal(key);

    exit(EXIT_SUCCESS);
}
