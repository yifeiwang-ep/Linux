#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

/*
 *
//保存跳转位置的栈信息
jmp_buf env;

//信号处理函数
void handler_sigrtmin15(int signo){
    printf("recv SIGRTMIN+15\n");
    longjmp(env, 1); //返回到env处
}

//信号处理函数
void handler_sigrtmax15(int signo){
    printf("recv SIGRTMAX-15\n");
    longjmp(env, 2);
}

int main(){
    //设置返回点
    switch(setjmp(env)){
        case 0:
            break;
        case 1:
            printf("return from SIGERMIN+15\n");
            break;
        case 2:
            printf("return from SIGETMAX-15\n");
            break;
        default:
            break;
    }

    signal(SIGRTMIN+15, handler_sigrtmin15);
    signal(SIGRTMAX-15, handler_sigrtmax15);

    while(1);

    return 0;
}

*
*/

#define ENV_UNSAVE 0
#define ENV_SAVED 1

int flag_saveenv = ENV_UNSAVE;
jmp_buf env;

void handler_sigrtmin15(int signo){
    if(flag_saveenv == ENV_UNSAVE){
        return;
    }

    printf("recv SIGRTMIN+15\n");
    sleep(10);
    printf("in handler_sigrtmin15, after sleep\n");
    siglongjmp(env, 1);

}

int main(){
    switch(sigsetjmp(env, 1)){
        case 0:
            printf("return 0\n");
            flag_saveenv = ENV_SAVED;
            break;
        case 1:
            printf("return from SIGRTMIN+15\n");
            break;
        default:
            printf("return else\n");
            break;
    }

    signal(SIGRTMIN+15, handler_sigrtmin15);

    while(1);
    return 0;
}
