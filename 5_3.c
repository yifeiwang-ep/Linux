#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int fd;

    int len = atoi(argv[2]);
    if(argc == 4){
        fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
        while(len--){
            if(write(fd,"t", 1) == -1){
                printf("fdsf\n");
            }
        }
    }
    else{
        fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        while(len--){
            lseek(fd, 0, SEEK_END);
            if(write(fd, "t", 1) == -1){
                printf("fdsf\n");
            }
        }
    }
}
