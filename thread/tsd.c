/*************************************************************************
	> File Name: tsd.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年08月01日 星期一 15时52分39秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
pthread_key_t key;

void* thread2(void *arg){
    int tsd = 5;
    printf("thread2 %u is running\n",pthread_self());
    pthread_setspecific(key, (void*)tsd);
    printf("thread2 %u returns %u\n",pthread_self(), pthread_getspecific(key));
}

void* thread1(void *arg){
    int tsd = 0;
    pthread_t thid2;
    
    printf("thread1 %u is running\n", pthread_self());
    pthread_setspecific(key, (void*)tsd);
    pthread_create(&thid2, NULL, thread2, NULL);
    sleep(5);
    puts("dfdsfdsfdsfsdfds");
    printf("thread1 %u returns %u\n",pthread_self(), pthread_getspecific(key));
}

int main(int argc,char *argv[])
{
    pthread_t thid1;
    
    printf("main thread beings running\n");
    pthread_key_create(&key, NULL);
    pthread_create(&thid1, NULL, thread1, NULL);
    sleep(3);
    pthread_key_delete(key);
    printf("main thread exit\n");

    return 0;
}
