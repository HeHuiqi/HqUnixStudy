#include "apue.h"
#include <sys/wait.h>
#define MAXLINE 1000
//编译说明
/*
·$ cc apue.c hq_exec.c
*/
//中断信号处理函数
void sig_int(int signo){
    printf("interrupt\n%%");
}
int main(int argc, char const *argv[])
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    printf("%% ");
    //捕捉中断信号
    if(signal(SIGINT,sig_int) == SIG_ERR){
        hq_err_sys("signal error");
    }
    while((fgets(buf,MAXLINE,stdin) != NULL)){
        if (buf[strlen(buf)-1] == '\n'){
            buf[strlen(buf)-1] =0;
        }
        if ((pid = fork()) < 0 ){
            hq_err_sys("fork error");
        }else if (pid == 0){
            execlp(buf,buf,(char *)0);
            hq_err_sys("can't execute");
            exit(127);
        }
        if((pid = waitpid(pid,&status,0)) < 0){
            hq_err_sys("waitpid error");
        }
        printf("%% ");

    }
    return 0;
}
