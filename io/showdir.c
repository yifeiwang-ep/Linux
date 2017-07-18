/*************************************************************************
	> File Name: showdir.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月22日 星期五 15时29分12秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>
int readd(char *path){
    DIR *dir;
    struct dirent *ptr;
    dir = opendir(path);
    if(dir == NULL){
        perror("opendir failed\n");
        return -1;
    }
    while((ptr = readdir(dir)) != NULL){
        printf("%s\n", ptr->d_name);
    }
    closedir(dir);
    return 0;
}

int main(int argc,char *argv[])
{
    if(argc < 2){
        perror("input wrong\n");
        return 0;
    }
    if(readd(argv[1]) < 0){
        return 0;
    }
    return 0;
}
