/*************************************************************************
	> File Name: chmod.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月19日 星期二 14时46分59秒
 ************************************************************************/
//利用chmod函数实现简化版的my_chmod
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
//假设输入的是777
int main(int argc,char *argv[])
{
    int mod;
    int mod_u;
    int mod_g;
    int mod_o;
   // char *path;
    if(argc<3){
        printf("mod number error");
        exit (0);
    }
    mod=atoi(argv[1]);
    if(mod>777||mod<0){
        printf("input mod error");
        exit (0);
    }
    mod_u=mod/100;
    mod_g=(mod-mod_u*100)/10;
    mod_o=mod-mod_u*100-mod_g*10;
    mod=mod_u*8*8+mod_g*8+mod_o;         //实质是将输入的！意义！为八进制的777转换成1十进制的
   // path=argv[2];
    if(chmod(argv[2],mod)!=0){
        perror("chmod error");
        exit(0);
    }
    return 0;
}
