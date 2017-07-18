/*************************************************************************
	> File Name: daemon.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月27日 星期三 20时47分07秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/param.h>      //what?
#include<unistd.h>
#include<sys/stat.h>
#include<syslog.h>        //系统日志
#include<time.h>
#include<signal.h>           //信号处理
#include<stdlib.h>

int init_daemon(void){
    int pid;
    int i;

    //忽略中终端信号
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();
    if(pid > 0){
        exit(0);  //结束父进程
    }
    else if(pid < 0){
        return -1;
    }
   
    setsid();

    pid = fork();
    if(pid > 0){
        exit(0);
    }
    else if(pid > 0){
        return -1;
    }

    for(i = 0;i < NOFILE; close(i++));
    chdir("/");

    umask(0);
    signal(SIGCHLD, SIG_IGN);
    return 0;
}

int main(int argc,char *argv[])
{
    time_t now;
    init_daemon();
    syslog(LOG_USER |LOG_INFO, "测试守护进程\n");
    while(1){
        sleep(8);
        time(&now);
        syslog(LOG_USER |LOG_INFO,"系统时间：\t%s\t\t\n",ctime(&now));
    }
    return 0;
}
