/*************************************************************************
	> File Name: lock.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月22日 星期五 08时15分49秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
//错误记录
void err (char *err_str, int line){
    fprintf(stderr, "%d :", line);
    perror(err_str);
}

//测试锁的可执行性

int getlk(int fd, struct flock *lock){
    int ret;
    ret = fcntl(fd, F_GETLK, lock);
    if(ret == 0){
        if(lock->l_type == F_UNLCK){
            puts("can be locked\n");
            return 0;
        }
        else{
            if(lock->l_type == F_RDLCK){
                printf("cant lock another read lock by %d\n", lock->l_pid);
            }
            else if(lock->l_type == F_WRLCK){
                printf("write lock has been locked by %d\n", lock->l_pid);
            }
            return -2;
        }
    }
    else{
        err("GETLOCK", __LINE__);
        return -1;
    }
}

//设置锁

int setlk(int fd, struct flock *lock){
    int ret;
    ret = fcntl(fd, F_SETLK, lock);
    if(ret == 0){
        if(lock->l_type == F_UNLCK){
            printf("unlocked by %d\n", getpid());
        }
        else if(lock->l_type == F_RDLCK){
            printf("set read lock by %d\n", getpid());
        }
        else if(lock->l_type == F_WRLCK){
            printf("set write lock by %d\n",getpid());
        }
        return ret;
    }
    else{
        err("setlock", __LINE__);
        return -1;
    }
}

//创建文件

int oc_file(){
    int fd;
    char read_buf[21];
    char filename[225];
    gets(filename);
    fd = open(filename, O_CREAT|O_APPEND|O_RDWR, S_IRWXU|S_IRGRP|S_IROTH);
    if(fd == -1){
        err("oc_file", __LINE__);
        exit(1);
    }
    if(write(fd, "testtesttestlocklock", 21) == -1){
        err("write", __LINE__);
        exit(1);
    }
    lseek(fd, 0 ,SEEK_SET);
    if(read(fd, read_buf, 21) == -1){              //或者小于len也是错；
        err("read", __LINE__);
        exit(1);
    }
    puts(read_buf);
    return fd;
}

//初始化锁

void trunc_lock(struct flock *lock){
    memset(lock, 0, sizeof(struct flock));
    lock->l_start = SEEK_SET;
    lock->l_whence = 0;
    lock->l_len = 0;
}
//设置读锁

void read_lock(int fd, struct flock *lock){
    lock->l_type = F_RDLCK;
    if(getlk(fd, lock) == 0){
        lock->l_type = F_RDLCK;
        setlk(fd, lock);
    }
}

//设置写锁

void write_lock(int fd, struct flock *lock){
    lock->l_type = F_WRLCK;
    if(getlk(fd, lock) == 0){
        lock->l_type = F_WRLCK;
        setlk(fd, lock);
    }
}

//释放锁

void un_lock(int fd, struct flock *lock){
    lock->l_type = F_UNLCK;
    setlk(fd, lock);
}


int main(int argc,char *argv[])
{
    struct flock lock;
    int fd;
    
    fd = oc_file();
    trunc_lock(&lock);
    read_lock(fd, &lock);
    getchar();                            // 多进程测试
    write_lock(fd, &lock);
    un_lock(fd, &lock);
    close(fd);
    return 0;
}
