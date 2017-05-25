#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd;
    fd = open("5_2test", O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    lseek(fd, 0, SEEK_SET);
    write(fd, "test", 4);
}
