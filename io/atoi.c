/*************************************************************************
	> File Name: atoi.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月19日 星期二 21时36分50秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int atoi(const char * nptr){
    char i= *nptr;
    int a[100]={0};
    int s=0,flag=1,mark,j;
    int number=0;
    int t;
    if(i == '\0')
        return 0;
    if(i=='-'){
        flag=-1;
        i= *++nptr;
    }
   /*
    while(i>='0'&&i<='9'){
        a[s++]=i-'0';
        i= *++nptr;
    }
    mark=s;
    if(mark==0)
        exit (1);
    for(t=0,j=mark-1;t<mark;t++,j--){
        a[t]=a[t]*pow(10,j);
        number+=a[t];
    }*/
    while(*nptr >= '0'&& *nptr <= '9'){
        number=number*10+*nptr++-'0';
    }
    return number*flag;
}
int main(int argc,char *argv[])
{
    char cptr[100];
    gets(cptr);
    printf("%d",atoi(cptr));
    return 0;
}
