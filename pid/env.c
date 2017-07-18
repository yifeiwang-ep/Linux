/*************************************************************************
	> File Name: env.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月27日 星期三 21时46分19秒
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<unistd.h>

extern char **environ;

int main(int argc,char *argv[])
{
    int i;
    
    printf("Argument:\n");
    for(i = 0;i < argc;i++){
        printf("argv[%d] is %s\n",i,argv[i]);
    }
    printf("environment\n");

    for(i = 0;environ[i] != NULL;i++){
        printf("%s\n",environ[i]);
    }
    return 0;
}
