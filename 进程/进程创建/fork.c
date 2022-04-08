// #include <sys/types.h>
// #include <unistd.h>

// pid_t fork(void);
//     函数作用：用于创建子进程
//     返回值：
//         会返回两次，一次父进程一次子进程。
//         在父进程中返回子进程的进程的ID，在子进程返回0。
//         区别父子进程通过fork的返回值。

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main() {
    //创建进程
    pid_t pid = fork();

    // 判断进程，如果大于0是父进程，等于0是子进程,getpid()当前进程id，getppid()父进程ID
    if(pid > 0) {
        printf("pid = = %d,\nparent,pid = %d, ppid = %d\n", pid, getpid(), getppid());
    }else if(pid == 0) {
        printf("child, pid = %d, ppid = %d\n", getpid(), getppid());
    }
    
    //分别在子进程和父进程交替执行for循环
    for(int i = 0; i < 3; i++) {
        printf("pid = %d, i = %d\n", pid, i);
        sleep(1);
    }
    return 0;
}