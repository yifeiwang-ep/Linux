#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char* argv[]){
    assert(argc == 2);
    char *host = argv[1];
    struct hostent* hostinfo = gethostbyname(host);
    assert(hostinfo);
    struct servent* servinfo = getservbyname("daytime", "tcp");
    assert(servinfo);

    printf("daytime port is %d\n", ntohs(servinfo->s_port));

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET6;
    address.sin_port = servinfo->s_port;
    address.sin_addr = *(struct in_addr* )*hostinfo->h_addr_list;
    int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    int result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
    if(result == -1){
        perror("connect");
    }
    assert(result != -1);

    char buffer[120];
    result = read(sockfd, buffer, sizeof(buffer));
    assert(result > 0);

    buffer[result] = '\0';
    printf("%d the daytime is %s", result, buffer);
    close(sockfd);
    return 0;

}
