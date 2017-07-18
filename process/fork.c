/*************************************************************************
	> File Name: fork.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月27日 星期三 08时44分56秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

//fork的返回值
/*
int main(int argc,char *argv[])
{
    pid_t pid;
    char *msg;
    int k;

    printf("proces creation study\n");
    pid = fork();
    switch(pid){
        case 0:{
            msg = "child process is running";
            k = 3;
            break;
        }
        case -1:{
            perror("prcess creation failed\n");
            break;
        }
        default:{
            msg = "parent process is running";
            k=5;
            break;
        }
    }
    while(k > 0){
        puts(msg);
        sleep(1);
        k--;
    }

    exit(0);
}

*/

//孤儿进程
/*
int main(int argc, char *argv[]){
    pid_t pid;

    pid = fork();
    switch(pid){
        case 0:{
            while(1){
                printf("A background process,PID:%d,parent id :%d\n",getpid(),getppid());
                sleep(3);
            }
        }
        case -1:{
            perror("process creation failed\n");
            exit(-1);
        }
        default:{
            printf("i am parent process ,my pid is %d\n",getpid());
            exit(0);
        }
    }
    return 0;
}

*/


//fork&vfork


int globVar = 5;

int main(int argc, char *argv[]){
    pid_t pid;
    int var = 1, i;

    printf("fork is diffrent with vforki\n");
    
    pid = fork();
   // pid = vfork();
    switch(pid){
        case 0:
        i = 3;
        while(i-- > 0){
            printf("child process is running\n");
            globVar++;
            var++;
            sleep(1);
        }
        printf("child's globVar = %d, var = %d\n",globVar, var);
        break;
        case -1:
        perror("process  creation failed\n");
        exit(0);
        default:
        i = 5;
        while(i-- > 0){
            printf("the parent process is running\n");
            globVar++;
            var++;
            sleep(1);
        }
        printf("parent's globVar = %d,var = %d\n",globVar, var);
        exit(0);
    }
}


