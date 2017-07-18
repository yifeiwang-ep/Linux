/*************************************************************************
	> File Name: wati.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月28日 星期四 10时19分43秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    char *msg;
    int k;
    int exit_code;
    printf("study how to get exit codes\n");
    pid = fork();
    switch(pid){
        case 0:{
            msg = "child process id running";
            k = 5;
            exit_code = 37;
            break;
        }
        case -1:{
            perror("process creation failed\n");
            exit(1);
        }
        default:{
            exit_code = 0;
            break;
        }
    }

    if(pid != 0){
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);
        printf("child process has exitd.pid = %d\n",child_pid);
        printf("parent process is %d\n",getpid());
        if(WIFEXITED(stat_val)){
            printf("child exited with code %d\n",WEXITSTATUS(stat_val));
        }
        else{
            printf("child exited abnormaly\n");
        }
    }
    else{
        while(k-- > 0){
            puts(msg);
            sleep(1);
        }
    }
    exit(exit_code);
}
