/*
    #include <stdlib.h>
    void exit(int status);

    #include <unistd.h>
    void _exit(int status);

    status参数：是进程退出时的一个状态信息。父进程回收子进程资源的时候可以获取到。
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    printf("hello\n");
    printf("world");

    //exit会刷新输入输出流，_exit不会刷新，world还在缓存区中，所以没有world
    //exit(0);输出  // hello 
                   // world

    _exit(0); //输出 hello
    
    return 0;
}