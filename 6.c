#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int psize = getpagesize();
    printf("%d\n", psize);
    return 0;
}

