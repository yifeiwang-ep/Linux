#define _LARGEFILE64_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    int fd;
    off64_t off;
    fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    off = atoll(argv[2]);
    if( lseek64(fd, off, SEEK_SET) == -1){
        printf("%s\n", "hahai");
    }

    if(write(fd, "test", 4) == -1){
        printf("%s\n", "haha");
    }

    exit(EXIT_SUCCESS);
}
