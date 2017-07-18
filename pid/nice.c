/*************************************************************************
	> File Name: nice.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月28日 星期四 13时49分05秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/resource.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    int stat_val = 0;
    int oldprl, newprl;

    printf("nice to study\n");
    pid = fork();
    switch(pid){
        case 0:
        printf("child is running,CurPid is %d,ParentPid is %d\n",pid,getppid());

        oldprl = getpriority(PRIO_PROCESS, 0);
        printf("Old  priority = %d\n",oldprl);

        newprl = nice(2);
        printf("New priority = %d\n",newprl);
        exit(0);

        case -1:
        perror("Process creationg failed\n");
        break;
        default:
        printf("Parent is running,ChildPid is %d, ParentPid is %d\n",pid, getpid());
        break;
    }

    wait(&stat_val);
    exit(0);
}


//nice的系统调用
/*
int nice(int increment){
    int oldprl = getpriority(PRIO_PROCESS, getpid());
    return setpriority(PRIO_PROCESS, getpid(), oldprl + increment);
}
*/
