#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int num = 0;
void *writenum(void *arg) {
    while(1) {
        num++;
        printf("write_thread_id: %ld, num: %d",pthread_self()->__sig,num);
        usleep(500);
    }
    return NULL;

}

void *readnum(void *arg) {
    while(1) {
        printf("read_thread_id: %ld, num: %d",pthread_self()->__sig,num);
        usleep(500);
    }
    return NULL;
    
}

int main() {
    pthread_t wtids[3];
    pthread_t rtids[5];

    for(int i = 0; i < 3; i++) {
        pthread_create(&wtids[i], NULL, writenum, NULL);
    }
    for(int i = 0; i < 4; i++) {
        pthread_create(&rtids[i], NULL, readnum, NULL);
    }

    for(int i = 0; i < 3; i++) {
        pthread_detach(wtids[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_detach(rtids[i]);
    }
    pthread_exit(NULL);

}