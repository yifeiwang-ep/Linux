/*************************************************************************
	> File Name: creat.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年08月01日 星期一 11时05分24秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

//创建线程

/*
int* c_pthread(){
    pthread_t npthread;

    npthread = pthread_self();
    printf("the new pthread id is:%u\n",npthread);
    return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t pth;
    
    printf("main pthread,id is %u\n",pthread_self());
    if(pthread_create(&pth, NULL, (void *)c_pthread, NULL) != 0){
        printf("creat new pthread failed\n");
        return 0;
    }
    sleep(1);
    return 0;
}
*/


//pthread_once

/*
pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void){
    printf("the function is running by pthread id %u\n",pthread_self());
}

void* thread1(void *arg){
    pthread_t tid = pthread_self();
    printf("current thread's id is %u\n",tid);
    pthread_once(&once, run);
    printf("thread1 ends\n");
}

void* thread2(void *arg){
    pthread_t tid = pthread_self();
    printf("current thread id is %u\n",tid);
    pthread_once(&once, run);
    printf("thread2 ends\n");
}

int main(){
    pthread_t thid1, thid2;

    pthread_create(&thid1, NULL, thread1, NULL);
    pthread_create(&thid2, NULL, thread2, NULL);
    sleep(3);
    printf("man thread exit\n");
    return 0;
}

*/


//pthread_join()

void assisthread(void *arg){
    printf("i am pretend to be doing some jobs\n");
    sleep(3);
    pthread_exit(0);
}

int main(){
    pthread_t assistid;
    int status;
    pthread_create(&assistid, NULL, (void *)assisthread, NULL);
    pthread_join(assistid, (void *)&status);
    printf("assisthread's exit is caused %d\n",status);

    return 0;
}
