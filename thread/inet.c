/*************************************************************************
	> File Name: inet.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年08月02日 星期二 10时47分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


//测试数据
//192.168.30.141
//255.255.255.255

int main(int argc,char *argv[])
{
    char buffer[32];
    int ret = 0;
    int host = 0;
    int network = 0;
    unsigned int address = 0;
    struct in_addr in;

    in.s_addr = 0;

    printf("please input ip address:\n");
    fgets(buffer, 31, stdin);
    buffer[31] = '\0';

    //aton
    if((ret = inet_aton(buffer, &in)) == 0){
        puts("wrong");
    }
    else{
        printf("inet_aton:\t0x%x\n", in.s_addr);
    }

    //inet_addr
    if((address = inet_addr(buffer)) == INADDR_NONE){
        puts("wrong");
    }
    else{
        printf("inet_addr:\t0x%x\n", in.s_addr);
    }

    //inet_network
    if((address = inet_network(buffer)) == -1){
        puts("wrong");
    }
    else{
        printf("inet_network:\t0x%x\n", in.s_addr);
    }

    //inet_ntoa
    if(inet_ntoa(in) == NULL){
        puts("wrong");
    }
    else{
        printf("inet_ntoa:\t%s\n", inet_ntoa(in));
    }

    //inet_lnaof&inet_netof
    host = inet_lnaof(in);
    network = inet_netof(in);
    printf("inet_lnaof:\t0x%x\n", host);
    printf("inet_netof:\t0x%x\n",network);

    in = inet_makeaddr(network, host);
    printf("inet_makeaddr:0x%x\n", in.s_addr);

    return 0;
}





