/*************************************************************************
> File Name: shell.c
> Author:wyf
> Mail:Catherine199787@outlook.com
> Created Time: 2016年07月30日 星期六 10时54分55秒
************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<malloc.h>

#define normal 0
#define out 1
#define in 2
#define pipe 3
void err(char* err_string, int line){
    perror(err_string);
    fprintf(stderr, "line:%d", line);
    return;
}

int right(char *arg){
    DIR *dir;
    struct dirent* ptr;
    char *path[] = {"./","/bin","/usr/bin/",NULL};
    int i;

    if(strncmp(arg, "./", 2) == 0){
        arg = arg + 2;
    }

    for(i = 0; path[i] != NULL; i++){
        dir = opendir(path[i]);
        if(dir == NULL){
            err("open_bin error", __LINE__);
        }
        while((ptr = readdir(dir)) != NULL){
            if(strcmp(ptr->d_name, arg) == 0){
                closedir(dir);
                return 1;
            }
        }
        closedir(dir);
    }
    return 0;
}


void my_history(){
    int fd;
    int len;
    int i;
    fd = open(".my_shell_history", O_RDWR );
    if(fd < 0){
        perror("open_history");
    }

    lseek(fd, 0 ,SEEK_END);
    len = lseek(fd, 0, SEEK_CUR);
    lseek(fd, 0, SEEK_SET);

    char read_buf[len];

    read(fd, read_buf, len);
    for(i = 0; i < len; i++){
            printf("%c", read_buf[i]);
    }
    close(fd);
}

void argpipe(char *argn[], char *arg[]){
    int pid;
    int status;
    int fd;

    pid = fork();
    if(pid < 0){
        err("pipe_fork", __LINE__);
    }

    else if(pid == 0){
        if(!right(arg[0])){
            err("pipe arg", __LINE__);
        }
        fd = open("/tmp/youdonotknowfile", O_WRONLY | O_CREAT | O_TRUNC,0644);
        dup2(fd, 1);
        execvp(arg[0], arg);
        exit(0);
    }

    if(waitpid(pid, &status, 0) == -1){
        err("pipe_wait", __LINE__);
    }
    if(!right(argn[0])){
        err("pipe_arg", __LINE__);
    }

    fd = open("/tmp/youdonotknowfile", O_RDONLY);
    dup2(fd, 0);
    execvp(argn[0], argn);

    if(remove("/tmp/youdonotknowfile")){
        err("remove", __LINE__);
    }
}
void arginput(char *buf){
    int len = 0;
    int i = 0;
    char ch;
    while(1){
        ch = getchar();
        if(ch == '\n'){
            break;
        }
        else if(ch == '\t' ){
            continue;
        }
        buf[i] = ch;
        i++;
    }
    buf[i] = '\n';

    len = strlen(buf);
    int fd;

    fd = open(".my_shell_history", O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP);
    int ret;
    ret = write(fd, buf, len);
    close(fd);
    if(len >= 255){
        err("arginput", __LINE__);
    }

    buf[i] = '\0';
}

void argexplain(char * buf, char arglist[][255], int *argcount)
{
    int number = 0;
    int i = 0;
    while(1){
        if(buf[i] == '\0'){
            break;
        }
        else if(buf[i] != ' '){
            arglist[*argcount][number] = buf[i];
            number++;
        }
        else{
            arglist[*argcount][number] = '\0';
            number = 0;
            *argcount = *argcount + 1;
        }
        i++;
    }

}


void argdo(int argcount, char arglist[][255]){
    char *arg[argcount+1];
    *arg = NULL;
    int wrong = 0;
    int how = 0;
    int background = 0;
    int fd;
    int i;
    int status;
    char path[100] = {'\0'};
    char *argn[argcount+1];
    pid_t pid;

    for(i = 0; i <= argcount ; i++){
        arg[i] = arglist[i];
    }
    arg[i] = NULL;
    if(strcmp(arg[0], "history") == 0 ){
        my_history();
        return;
                }
    for(i = 0; i <= argcount; i++){
        if(strcmp(arg[i], "&") == 0){
            if(i == (argcount - 1)){
                background = 1;
                arg[argcount-1] = NULL;
                break;
            }
            else{
                err("too many '&'", __LINE__);
                return;
            }
        }
    }

    for(i = 0; arg[i] != NULL; i++){
        if(strcmp(arg[i], ">") == 0){
            wrong++;
            how = out;
            if(arg[i+1] == NULL){
                wrong++;
            }
        }
        else if(strcmp(arg[i], "<") == 0){
            wrong++;
            how = in;
            if(arg[i+1] == NULL){
                wrong++;
            }
        }
        else if(strcmp(arg[i], "|") == 0){
            wrong++;
            how = pipe;
            if(arg[i+1] == NULL){
                wrong++;
            }
            else if(i == 0){
                wrong++;
            }
        }
    }

    if(wrong > 1){
        err("too many arg", __LINE__);
    }
    pid = fork();
    if(pid < 0){
        err("fork error", __LINE__);
    }

    switch(how){
        case 0:{
            if(pid == 0){
                if( !right(arg[0]) ){
                    exit(0);
                }
                execvp(arg[0], arg);
                exit(0);
            }
        }
        break;
        case 1:{
            for(i = 0; arg[i] != NULL; i++){
                if(strcmp(arg[i], ">") == 0){
                    strcpy(path, arg[i+1]);
                    arg[i] = NULL;
                }
            }

            if(pid == 0){
                if( !right(arg[0]) ){
                    err("wrong arg", __LINE__);
                }
                printf("%s\n",path);
                fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
                if(fd < 0){
                    err("open faild", __LINE__);
                }
                dup2(fd, 1);
                execvp(arg[0], arg);
            }
        }
        break;
        case  2:{
            for(i = 0; arg[i] != NULL; i++){
                if(strcmp(arg[i], "<") == 0){
                    strcpy(path, arg[i+1]);
                    arg[i] = NULL;
                }
            }
            if(pid == 0){
                if( !right(arg[0]) ){
                    err("wrong arg", __LINE__);
                }
                fd = open(path, O_RDONLY);
                if(fd < 0){
                    err("open faild", __LINE__);
                }
                dup2(fd, 0);
                execvp(arg[0], arg);
                exit(0);
            }
        }
    break;
case 3:{
    for(i = 0; arg[i] != NULL; i++){
        if(strcmp(arg[i], "|") == 0){
            arg[i] = NULL;
            int j;
            for(j = i+1; arg[j] != NULL; j++){
                argn[j-i-1] = arg[j];
            }
            argn[j-1-i] = NULL;
            break;
        }
    }
    if(pid == 0){
        argpipe(argn, arg);
    }
}
break;
        default:
            break;
    }//switch

    if(background == 1){
        return ;
    }
    if(waitpid(pid, &status, 0) == -1){
        err("wait for chil error", __LINE__);
    }
    }

int main(int argc,char *argv[]){
    char *buf;
    int argcount = 0, i;
    char arglist[100][225];
    char **arg;

    buf = (char *)malloc(255);
    if(buf == NULL){
        err("malloc", __LINE__);
    }

    while(1){
        arg = NULL;
        memset(buf, 0 ,256);
        printf("my_shell$$");
        arginput(buf);
        puts(buf);
        if(strcmp(buf, "exit") == 0 || strcmp(buf, "logout") == 0)
        {
            break;
        }
        for(i = 0; i < 100; i++){
            arglist[i][0] = '\0';
        }
        argcount = 0;
        argexplain(buf, arglist, &argcount);
        argdo(argcount, arglist);
    }
    if(buf != NULL){
        free(buf);
        buf = NULL;
    }

    return 0;
}
