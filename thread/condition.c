/*************************************************************************
	> File Name: condition.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年08月01日 星期一 17时48分33秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void * thread1(void *arg){
    
    //pthread_cleanup_push(pthread_mutex_unlock, &mutex);

    while(1){
        printf("thread1 is running\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        printf("thread1 applied the condition\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    //pthread_cleanup_pop(0);
}

void *thread2(void *arg){
    while(1){
        printf("thread2 is running\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        printf("thread2 appliced the condition\n");
        pthread_mutex_unlock(&mutex);
        sleep(4);
    }
}

int main(int argc,char *argv[])
{
    pthread_t tid1, tid2;

    printf("condition varilable study!\n");
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    do{
        pthread_cond_signal(&cond);
    }while(1);

    sleep(50);
    
    pthread_exit(0);
}
