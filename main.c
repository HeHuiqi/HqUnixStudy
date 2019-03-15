
#include "apue.h"
#include <limits.h>
#include <fcntl.h>
#define BUFFSIZE 4096

void hqls(int argc,const char *dir)
{
    if (argc != 2)
    {
        printf("usage:ls directory_name\n");
        return ;
    }
    DIR *dp;
    struct dirent *dirp;

    printf("argv[1]==%s\n", dir);
    dp = opendir(dir);
    int i = 0;
    if (dp != NULL)
    {
        printf("open %s\n", dir);
        while ((dirp = readdir(dp)) != NULL)
        {
            printf("%s\n", dirp->d_name);
            i++;
        }
    }
    closedir(dp);
}
// $ ./a.out > data
// $ ./a.out < data > file.text
void buf_copy()
{
    ssize_t n;
    char buf[BUFFSIZE];
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            printf("write error!");
        }
        if (n < 0)
        {
            printf("read error!");
            exit(0);
        }
    }
}
void std_copy(){
    int c;
    while((c = getc(stdin)) != EOF){
        if(putc(c,stdout) == EOF){
            hq_err_sys("output error");
        }
        if (ferror(stdin)){
            hq_err_sys("input eror");
        }
    }
}


// 读取apue.h文件的内容
void readFile(){

 int fid = open("apue.h",O_RDONLY);
    if(fid){
        ssize_t n;
        char buf[200];
        while ((n = read(fid, buf, BUFFSIZE)) > 0)
        {
            printf("n==%ld",n);
            if (n < 0 || n == EOF)
            {
                printf("read error!");
                exit(0);
            }
        }
        printf("buf==%s\n", buf);
    }
}

//编译说明
/*
$ cc apue.c main.c
#执行
$ ./a.out
*/
int main(int argc, char const *argv[]){

    printf("Unix Study\n");
    // hqls(argc,argv[1]);
    // buf_copyls();

    // std_copy();

    // printf("progress ID %d\n",getpid());

    // fprintf(stderr,"EACCES: %s\n",strerror(EACCES));
    // errno = ENOENT;
    // perror(argv[0]);

    // printf("uid = %d, gid = %d \n",getuid(),getgid());
    // printf("name_length == %ld \n",sysconf(_SC_CLK_TCK));

   readFile();

    return 0;
}
