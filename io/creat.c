/*************************************************************************
	> File Name: creat.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com mZ	> Created Time: 2016年07月20日 星期三 20时41分31秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>   
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
    int fd;
    char filename[255];
    gets(filename);
    
    if(fd = open(filename ,O_CREAT | O_EXCL , S_IRUSR | S_IWUSR)==-1){
    //if(fd = open(filename ,O_CREAT | O_WRONLY | O_TRUNC)==-1){
    
        //int errno;
        //errno = 1; //errno 可以人为的赋值
        
        perror("open");
        //相当于
        //printf("open: %s with errno %d /n",strerror(errno),errno);           //会出错，有问题。
        
        exit(1);
    }
    else
    {
        printf("success!");
    }
    close(fd);
    return 0;
}
