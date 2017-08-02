#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

static _Bool stop = false;

static void handle_term(int sig){
    stop = true;
}

int main(int argc, char* argv[]){
    signal (SIGTERM, handle_term);
    if(argc <= 3){
        puts("useerror");
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_family);
    address.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));

    ret = listen(sock, backlog);
    if(ret == -1){
        perror("bind");
        return 0;
    }
    assert(ret != -1);


    while(!stop){
        sleep(1);
    }

    close(sock);
    return 0;
}
