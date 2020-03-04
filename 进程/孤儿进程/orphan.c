#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    //创建一个子进程
    pid_t pid = fork();
    //创建失败
    if(pid < 0)
    {
        perror("fork error:");
        exit(1);
    }
    //子进程
    if(pid == 0)
    {
        printf("I am the chilid process.\n");
        printf("pid: %d\t ppid: %d\n",getpid(),getppid());

        //子进程睡眠1s，保证父进程先退出
        sleep(5);

        printf("pid: %d\t ppid: %d\n",getpid(),getppid());
        printf("child process has exited\n");
    }
    //父进程
    else
    {
        printf("I am father process\n");
        printf("pid: %d\n",getpid());
        //父进程睡眠1s，保证子进程正确输出进程id
        sleep(1);

        printf("father process has exited\n");
    }

    return 0;
}
