/*************************************************************************
	> File Name: rwl.c
	> Author:wyf
	> Mail:Catherine199787@outlook.com
	> Created Time: 2016年07月21日 星期四 10时29分55秒
 ************************************************************************/

//有遗留问题：空文件的打开read;


#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
int err(char* str_error,int line){
    fprintf(stderr , "%d :", line);
    perror(str_error);
    exit(1);
}

int flength(int fd){
    int length;
    if(lseek(fd ,0 ,SEEK_END)== -1){
        err("lseek set", __LINE__);
    }
    if((length = lseek(fd , 0 , SEEK_CUR)) == -1 ){
        err("length" , __LINE__);
    }
    if(lseek(fd , 0 ,SEEK_SET)== -1){
        err("lseek end" , __LINE__);
    }
    return length;
}

int co_file(){
    char filename[225];
    gets(filename);
    int fd;
    //fd = creat(filename, S_IRWXU);                  //creat打开的文件只能写不能读，要读就close再open ;
    fd=open(filename , O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(fd == -1){
        err("open or creat", __LINE__);
    }
    return fd;
}

int my_read(int fd ){
    char read_buf[100];
    int re,len;
    memset(read_buf, 0, sizeof(read_buf));
    len = flength(fd);
    if(len == 0){
        return 0;
    }
    if((re = read(fd , read_buf , len)) == -1){
        err("read", __LINE__);
    }
    puts(read_buf);
    return re;
}
void my_write(int fd){
    char write_buf[100];
    int we;
    gets(write_buf);
    int len = strlen(write_buf);
    we = write(fd , write_buf, len);
    if(we != len){
        err("write", __LINE__);
    }
}

int main(int argc,char *argv[])
{
    int fd;
    fd = co_file();
    if(flength(fd) > my_read(fd)){
        err("firstread", __LINE__);
    }
    my_write(fd);
    my_read(fd);
    close(fd);
    return 0;
}
