#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<time.h>
#include<string.h>


int getdtablesize();
//守护进程初始化函数
void init_deamon()
{
    //创建子进程
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error:");
        exit(1);
    }

    //退出父进程
    if(pid != 0)
    {
        exit(0);
    }
     
    //子进程开启新会话，并成为新会话的首进程和组长进程
    setsid();

    //创建第二子进程并结束第一子进程
    //第二子进程不再是会话首进程
    pid = fork();
    if(pid < 0)
    {
        perror("fork error:");
        exit(1); 
    }
    if(pid != 0)
    {
        exit(1);
    }

    //改变当前工作目录
    chdir("./");

    //重设文件掩码
    umask(0);

    //关闭打开的文件描符
    for(int i=0;i<getdtablesize();++i)
    {
        close(i);
    }

    return;
}


int main(int argc,char* argv[])
{
    int fp;
    time_t t;
    char* datetime;
    int len = 0;
    
    //初始化Deamon进程
    init_deamon();
    
    //每隔1分钟记录一次运行状态
    while(1)
    {
        fp = open("./Daemon.log",O_CREAT|O_WRONLY|O_APPEND,0600);
        if(fp == -1)
        {
            perror("open file error:");
            exit(1);
        }
        t = time(NULL);
        datetime = asctime(localtime(&t));
        len = strlen(datetime); 
        write(fp,datetime,len);
        close(fp);
        sleep(60);
    }
    
    return 0;
}

























