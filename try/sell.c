#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int ticket = 100;
void *selltickets(void *arg) {
    while(ticket > 0){
        usleep(3000);
        printf("id: %ld, ticket: %d\n", pthread_self()->__sig,ticket);
        ticket--;
    }
    return NULL;
}
int main() {
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, selltickets, NULL);
    pthread_create(&tid2, NULL, selltickets, NULL);
    pthread_create(&tid2, NULL, selltickets, NULL);
    
    //主线程回收结束的线程
    pthread_join(tid1,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid1,NULL);
    // 设置线程分离，自动回收
    // pthread_detach(tid1);
    // pthread_detach(tid2);
    // pthread_detach(tid3);

    pthread_exit(NULL);
    return 0;
}