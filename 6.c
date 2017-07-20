#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <stdlib.h>

static jmp_buf env;

/*
int main(int argc, char *argv[]){
    int psize = getpagesize();
    printf("%d\n", psize);
    return 0;
}
*/

static void dojump(int nvar, int rvar, int vvar){
    printf("inside dojump(): nvar=%d, rvar=%d, vvar=%d\n", nvar, rvar, vvar);
    longjmp(env, 1);
}



int main(){
    int nvar;
    register int rvar;
    volatile int vvar;

    nvar = 111;
    rvar = 222;
    vvar = 333;

    if(setjmp(env) == 0){
        nvar = 777;
        rvar = 888;
        vvar = 999;
        dojump(nvar, rvar, vvar);
    }
    else{
        printf("after longjmp():nvar=%d, rvar=%d, vvar=%d\n", nvar, rvar, vvar);
    }
}

