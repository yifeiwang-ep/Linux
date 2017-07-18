#include <stdio.h>
#include<signal.h>

void handler_sigint(int signo){
    printf("recv SIGINT\n");
}

//按下ctrl+c

int main(){
    signal(SIGINT, handler_sigint);

    while(1);

    return 0;
}
