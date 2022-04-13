#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
struct Node {
    int num;
    struct Node *next;
};

struct Node *head = NULL;

void *producer(void *arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->num = rand() %1000;
        newNode->next = head;
        head = newNode;
        printf("add node, nums: %d, pid: %ld\n", newNode->num, pthread_self()->__sig);
        usleep(100);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *consumer(void *arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        
        struct Node*temp = head;
        temp = temp->next;
        printf("del node, nums: %d, ctid: %ld", head->num, pthread_self()->__sig);
        free(head);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t ptids[5], ctids[5];
    pthread_mutex_init(&mutex,NULL);

    for(int i = 0; i < 5; i++) {
        pthread_create(&ptids[i],NULL,producer,NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&ctids[i],NULL,consumer,NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_detach(ctids[i]);
        pthread_detach(ptids[i]);
    }

    while(1) {
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);

    return 0;
}
