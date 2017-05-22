#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    size_t len;
    off_t offset;
    int fd, ap, j;
    char *buf;
    ssize_t numRead, numWritten;

    if(argc < 3 || strcmp(argv[0], "--help") == 0){
        //
    }

    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSER | S_IWUSER | S_IRGRP | S_IWGRP | \
            S_IWOTH | S_IROTH);
    if(fd == -1){
        //
    }

    for(ap = 2; ap < argc; ap++){
        switch(argv[ap][0]){
            case 'r':
            case 'R':
                len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                buf = malloc(len);
                if(buf == NULL){
                    //
                }
                numRead = read(fd, buf, len);
                if(numRead == -1){
                    //
                }

                if(numRead == 0){

                }
                else{
                    printf("%s: ", argv[ap]);
                    for(j = 0; j < numRead; j++){
                        if(argv[ap][1] == 'r'){
                            printf("%c\n", (unsined char)buf[j] ? buf[j] : '?');
                        }
                        else if(argv[ap][1] == 'R'){
                            printf("%02x", (unsineg char)buf[j]);
                        }
                    }
                    printf("\n");
                }
            free(buf);
            break;
            case 'w':
                numWritten =
        }
    }
}
