#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in serveraddr;
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd,(struct sockaddr *) &serveraddr,sizeof(serveraddr));
    
    if(ret == -1) {
        perror("connet");
        exit(-1);
    }

    write(fd,"client", 7);

    char recvBuf[1024] ={0};
    int len = read(fd,recvBuf,sizeof(recvBuf));
    if(len == -1) {
        perror("read");
        exit(-1);
    }else if(len > 0) {
        printf("recv server data: %s\n", recvBuf);
    }else if(len == 0) {
        printf(" server disconnent");
    }

    close(fd);

    return 0;
}