/*************************************************************************
	> File Name: ls.c
	> Author:wyf 
	> Mail:Catherine199787@outlook.com 
	> Created Time: 2016年07月22日 星期五 17时15分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<time.h>
#include<grp.h>
#include<pwd.h>
#include<limits.h>
#include<math.h>

#define FCOUNT 40
#define MAXROWLEN 80
#define FNAME_LEN 80
#define PARAM_NONE 0
#define PARAM_A 1
#define PARAM_L 2
#define PARAM_R 4
#define PARAM_D 8


/****通用的操作函数****/

//my_error
void err(char *str,int line ){
    fprintf(stderr, "LINE:%d", line);
    perror(str);
    exit(0);
}

//得到文件名数组并排序
char** fsort(DIR *dir)
{
	int i = 0;
    char asd[FNAME_LEN];
	char temp[FNAME_LEN];
	struct dirent *ptr;
    int index[FCOUNT];
    int count = 0;
    char** filenames = (char**)malloc(sizeof(char*)*FCOUNT);
    
    for(i=0; i<FCOUNT; i++){
        filenames[i] = (char*)malloc(sizeof(char)*FNAME_LEN);
        index[i] = i;
    }
	//获得文件名数组    
    while((ptr = readdir(dir)) != NULL){
        strcpy(asd, ptr->d_name);
        if(asd[0] == '.'){
            continue;
        }
        strcpy(filenames[count], ptr->d_name);
        count++;
    }
    
    int j = count - 1;
    
    closedir(dir);
    
    int t;
	
    for(i = 1;i < count; i++){
       
        strcpy(temp,filenames[i]);	
       
        for(j = i -1;j >= 0 && (strcmp(temp, filenames[j]) < 0); j--){
	        strcpy(filenames[ j+1 ], filenames[ j ]);	
		}
        
        strcpy(filenames[index[ j+1 ]], temp);	
	}
    
    for(i = 0; i < count; i++){
        filenames[i][FNAME_LEN] = filenames[index[i]][FNAME_LEN];
    }

    return filenames;
}

//得到全部文件名数组并排序
char** afsort(DIR *dir)
{
	int i = 0;
	char temp[FNAME_LEN];
	struct dirent *ptr;
    int index[FCOUNT];
    int count = 0;
    char** afilenames = (char**)malloc(sizeof(char*)*FCOUNT);
    
    for(i=0; i<FCOUNT; i++){
        afilenames[i] = (char*)malloc(sizeof(char)*FNAME_LEN);
        index[i] = i;
    }
	//获得文件名数组    
    while((ptr = readdir(dir)) != NULL){
        strcpy(afilenames[count], ptr->d_name);
        count++;
    }
    
    int j = count - 1;
    
    closedir(dir);
    
    int t;
	
    for(i = 1;i < count; i++){
       
        strcpy(temp,afilenames[i]);	
       
        for(j = i -1;j >= 0 && (strcmp(temp, afilenames[j]) < 0); j--){
	        strcpy(afilenames[ j+1 ], afilenames[ j ]);	
		}
        
        strcpy(afilenames[index[ j+1 ]], temp);	
	}
    
    for(i = 0; i < count; i++){
        afilenames[i][FNAME_LEN] = afilenames[index[i]][FNAME_LEN];
    }

    return afilenames;
}


//打开目录
DIR * openf(char *filename){
    DIR *dir;
   
    dir = opendir(filename);
    if(dir == NULL){
        err("open", __LINE__);
    }
    return dir;
}
//得到g_maxlen

int maxlen(char *path){
    DIR *dir;
    int g_maxlen = 0;
    struct dirent *ptr;
    dir = openf(path);
    while((ptr = readdir(dir)) != NULL){
        if(strlen(ptr->d_name) > g_maxlen){
            g_maxlen = strlen(ptr->d_name);
        }
    }
    closedir(dir);
    return g_maxlen;
}


//得到FCOUNT

int fcount(char * path){
    DIR *dir;
    char asd[FNAME_LEN];
    int count = 0;
    struct dirent *ptr;
    
    dir = openf(path);
    while((ptr = readdir(dir)) != NULL){
        strcpy(asd, ptr->d_name);
        if(asd[0] == '.'){
            continue;
        }
        count++;
    }
    return count;
}
int afcount(char * path){
    DIR *dir;
    int count = 0;
    struct dirent *ptr;
    
    dir = openf(path);
    while((ptr = readdir(dir)) != NULL){
        count++;
    }
    return count;
}


//对隐藏文件的摘   unfinish
int  _filenames(char *filename){
    int i;
    char temp = *filename;
    if(*filename == '.');
}



/*****ll目录文件*************/

//获取文件属性
struct stat llstat(char *filename){
    struct stat buf;
    if((lstat(filename, &buf))== -1){
        err("stat", __LINE__);
    }
    return buf;
}

//打印ll
void l_print(struct stat buf){
    char buf_time[32];           //why
    struct passwd *psd;
    struct group *grp;
    
    //类型
    if(S_ISLNK(buf.st_mode)){
        printf("l");
    }
    else if(S_ISREG(buf.st_mode)){
        printf("-"); 
    }
    else if(S_ISDIR(buf.st_mode)){
        printf("d");
    }
    else if(S_ISCHR(buf.st_mode)){
        printf("c");
    }
    else if(S_ISBLK(buf.st_mode)){
        printf("b");
    }
    else if(S_ISFIFO(buf.st_mode)){
        printf("p");
    }
    else if(S_ISSOCK(buf.st_mode)){
        printf("s");
    }

    //所有者操作权限
    if(buf.st_mode & S_IRUSR){
        printf("r");
    }else{
        printf("-");   
    }
    if(buf.st_mode & S_IWUSR){
        printf("w");
    }else{
        printf("-");
    }
    if(buf.st_mode & S_IXUSR){
        printf("x");
    }else{
        printf("-");
    }

    //用户组操作权限
    if(buf.st_mode & S_IRGRP){
        printf("r");
    }else{
        printf("-");   
    }
    if(buf.st_mode & S_IWGRP){
        printf("w");
    }else{
        printf("-");
    }
    if(buf.st_mode & S_IXGRP){
        printf("x");
    }else{
        printf("-");
    }

    //其他用户操作权限
    if(buf.st_mode & S_IROTH){
        printf("r");
    }else{
        printf("-");   
    }
    if(buf.st_mode & S_IWOTH){
        printf("w");
    }else{
        printf("-");
    }
    if(buf.st_mode & S_IXOTH){
        printf("x");
    }else{
        printf("-");
    }

    printf(" ");
    
    printf("%3d ",buf.st_nlink);
    
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%4s",psd->pw_name);
    printf("%4s",grp->gr_name);
    
    if( buf.st_size < 1024){
        printf(" %6d",buf.st_size);
    }
    else if(buf.st_size >=1024 && buf.st_size < pow(2, 16)){
        printf("%6.1fk",(float)buf.st_size/1024.0);
    }
    else if (buf.st_size >= pow(2,16) && buf.st_size < pow(2, 32)){
        printf("%6.1fM",(float)buf.st_size/pow(2,16));
    }
    
    strcpy(buf_time, ctime(&buf.st_mtime));
    buf_time[strlen(buf_time) - 1] = '\0';  
    printf("  %-s",buf_time);

} 


//获取全部文件属性


void ll_all(char **filenames, int count){
    struct dirent *ptr;
    struct stat buf;
    int i = 0;
    while(i < count){
        buf = llstat(filenames[i]);
        l_print(buf);
        printf("  %s\n",filenames[i]);
        i++;
    }
}

void lr_all(char **filenames, int count){
    struct dirent *ptr;
    struct stat buf;
    int i = 0;
    while(count--){
        buf = llstat(filenames[count]);
        l_print(buf);
        printf("  %s\n",filenames[count]);
    }
}
//打印总用量
void sum_size(DIR *dir){
    int sum; 
    struct dirent *ptr;
    struct stat buf;
    
    while((ptr = readdir(dir)) != NULL){
        stat(ptr->d_name, &buf);
        sum += buf.st_size;
    }
    printf("总用量  %ldK\n",sum);
    closedir(dir);
}

/***ls正确格式的目录名****/

//逆序输出
void nxprint(char **filenames, int g_maxlen, int count){
    
    int len;
    int g_leave_len = MAXROWLEN;
    while(count--){
        
        if(g_leave_len < g_maxlen){
            printf("\n");
            g_leave_len = MAXROWLEN;
        }
        len = g_maxlen - strlen(filenames[count]);
        g_leave_len -= g_maxlen;
        printf("%-s", filenames[count]);
        while(len--){
            printf(" ");
        }
    }
}

//正序输出
void zxprint(char **filenames, int g_maxlen, int count){
    
    int i, len;
    int g_leave_len = MAXROWLEN;

    for(i = 0;i < count; i++){
        
        if(g_leave_len < g_maxlen){
            printf("\n");
            g_leave_len = MAXROWLEN;
        }
        len = g_maxlen - strlen(filenames[i]);
        g_leave_len -= g_maxlen;
        printf("%-s", filenames[i]);
        while(len--){
            printf(" ");
        }

    }
}


void printfdir(char *path, int depth) {

    DIR * dir; 
    struct dirent *ptr; 
    struct stat buf;  
    int g_leave_len = MAXROWLEN;
    int len, g_maxlen = 20;
	
    dir = openf(path);
    chdir(path); 
    while ((ptr = readdir(dir)) != NULL) {
        lstat(ptr->d_name, &buf);
        if (S_ISDIR(buf.st_mode)) { 
            if (strcmp(".", ptr->d_name) == 0 || strcmp("..", ptr->d_name) == 0) {
                continue;
            }
            printf("\n\n%s/:\n", ptr->d_name);
            printfdir(ptr->d_name, depth + 4);
        } else {
            printf("%s",ptr->d_name);
        }
    }
    chdir("..");
    closedir(dir);
}

int main(int argc,char *argv[]){
    int i, j = 0, k, num = 0;
    DIR *dir;
    char path[MAXROWLEN];
    char param[32];
    struct stat buf;
    for(i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            for(k = 1; k < strlen(argv[i]); k++,j++){
                param[j] = argv[i][k];
            }
            num++;
        }
        else{
        strcpy(path, argv[i]);
        if(path[strlen(argv[i])-1] != '/'){
            path[ strlen(argv[i]) ] = '/';
            path[ strlen(argv[i]) + 1] = '\0';
        }
        }
    }
    param[j] = '\0';

    if((num + 1) == argc ){
        strcpy(path, "./");
        path[2] = '\0';
    	}
    i = 1;     

    int number = j;
	 
    if(j == 1 ){
        number = 0;
        switch(param[number]){
            case 'l':
                if((num + 1) == argc ){
                strcpy(path, "./");
                path[2] = '\0';
                dir = openf(path);
                sum_size(dir);
                dir = openf(path);
                ll_all(fsort(dir), fcount(path));
                return 0;
    	        }
                do{
                    if(argv[i][0] == '-'){
                        i ++;
                        continue;
                    }
                    strcpy(path, argv[i]);
                    if(stat(path, &buf) == -1){
                        err("main_stat", __LINE__);
                    }
					if(S_ISDIR(buf.st_mode)){
                        if(path[strlen(argv[i])-1] != '/'){
                            path[ strlen(argv[i]) ] = '/';
                            path[ strlen(argv[i]) + 1] = '\0';
                        }
                        else{
                            path[ strlen(argv[i]) ] = '\0';
                        }
                        dir = openf(path);
                        chdir(path);
                        sum_size(dir);
                        dir = openf(path);
                        ll_all(fsort(dir), fcount(path));
                        i++;
                    }
                    else{
                        chdir(path);
					    buf = llstat(path);
                        l_print(buf);
                        printf(" %s\n",path);
                        i++;
                    }
                }while(i < argc);
            break;
            case 'r':{
                puts(path);
                int len = maxlen(path) + 2;
                dir =  openf(path);
                chdir(path);
                nxprint(fsort(dir), len, fcount(path));
            }
            break;
            case 'a':{
                int len = maxlen(path) + 2;
                dir =  openf(path);
                zxprint(afsort(dir), len, afcount(path));
            }
            break;
            case 'R':{
				printfdir(path,0);										    
				break;
            }   
        }
        return 0;
    }
    else if(j == 2 || j == 3){
        int status = 0;
        while(number--){
            status |= param[number];
        }
        printf("%d",status);
        switch(status){
            case 109:{
                dir = openf(path);
				chdir(path);
                sum_size(dir);
                dir = openf(path);
                ll_all(afsort(dir), fcount(path));
            } 
            break;
            case 115:{
                int len = maxlen(path) + 2;
                dir =  openf(path);
                nxprint(afsort(dir), len, afcount(path));
            }
            break;
            case 126: 
                dir = openf(path);
				chdir(path);
                sum_size(dir);
                dir = openf(path);
                lr_all(fsort(dir), fcount(path));
                break;
               // case 10 : //lR 
               // case 12 : //Rr
                case 127:{
                    dir = openf(path);
				    chdir(path);
                    sum_size(dir);
                    dir = openf(path);
                    lr_all(afsort(dir), afcount(path));
                }
                break;
        }
        return 0;
    }
    else{
        int len = maxlen(path) + 2;
        dir =  openf(path);
        chdir(path);
        zxprint(fsort(dir), len, fcount(path));
        return 0;
    }
    return 0;
}
        /*
        else if(num == 0){
            strcpy(path,argv[i]);
            
            if(stat(path, &buf) == -1){
                err("main_stat", __LINE__);
            }
            if(S_ISDIR(buf.st_mode)){
                if(path[strlen(argv[i])-1] != '/'){
                    path[ strlen(argv[i]) ] = '/';
                    path[ strlen(argv[i]) + 1] = '\0';
                }
                else{
                    path[ strlen(argv[i]) ] = '\0';
                }
            int len = maxlen(path) + 2;
            dir =  openf(path);
            zxprint(fsort(dir), len, fcount(path));
            }
            return 0;
        }
        else{
            strcpy(path,argv[i]);
            
            if(stat(path, &buf) == -1){
                err("main_stat", __LINE__);
            }

            if(S_ISDIR(buf.st_mode)){
                if(path[strlen(argv[i])-1] != '/'){
                    path[ strlen(argv[i]) ] = '/';
                    path[ strlen(argv[i]) + 1] = '\0';
                }
                else{
                    path[ strlen(argv[i]) ] = '\0';
                }
                //ll目录
                dir = openf(path);
				chdir(path);
                sum_size(dir);
                dir = openf(path);
                ll_all(fsort(dir), fcount(path));
                i++;
            }
            else{
                l_print(buf);
                printf(" %s",path);
                puts("");
                i++;
            }
        }
    }while( i < argc );*/
//   return 0;
//}

