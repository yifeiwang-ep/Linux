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

int flength(int fd){
    int length;
    if(lseek(fd ,0 ,SEEK_END)== -1){
        my_err("lseek set", __LINE__);
    }
    if((length = lseek(fd , 0 , SEEK_CUR)) == -1 ){
        my_err("length" , __LINE__);
    }
    if(lseek(fd , 0 ,SEEK_SET)== -1){
        my_err("lseek end" , __LINE__);
    }
    return length;
}


char * my_read(int fd,int len){
    char read_buf[len+1];
    int re;
    memset(read_buf, 0, sizeof(read_buf));
    if((re = read(fd , read_buf , len)) == -1){
        my_err("c_read", __LINE__);
    }
    return read_buf;
}
void my_write(int fd){
    char write_buf[100];
    int we;
    gets(write_buf);
    int len = strlen(write_buf);
    we = write(fd , write_buf, len);
    if(we != len){
        my_err("c_write", __LINE__);
    }

}


int main(int argc,char *argv[])
{
    int fd;
    fd = co_file();
    if(flength(fd) > my_read(fd)){
        my_err("firstread", __LINE__);
    }
    my_write(fd);
    my_read(fd);
    close(fd);
    return 0;
}
