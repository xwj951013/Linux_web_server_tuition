#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    // 创建子进程
    pid_t pid = fork();

    // 判断是父进程还是子进程
    if(pid > 0) {

        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());

    } else if(pid == 0) {
        sleep(1);   //让父进程先结束
        // 当前是子进程
        printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());
       
    }

    // for循环
    for(int i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i , getpid());
    }

    return 0;
}

// i am parent process, pid : 62620, ppid : 62616
// i : 0 , pid : 62620
// i : 1 , pid : 62620
// i : 2 , pid : 62620
// i am child process, pid : 62621, ppid : 1  这里父进程ppid为1，因为父进程结束，子进程的父进程被置为init进程
// i : 0 , pid : 62621
// i : 1 , pid : 62621
// i : 2 , pid : 62621