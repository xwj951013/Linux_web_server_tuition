#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int lfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family =AF_INET;
    inet_pton(AF_INET,"192.168.1.102", &sockaddr.sin_addr.s_addr);
    sockaddr.sin_port = htons(9999);
    int ret =bind(lfd,(struct sockaddr *)&sockaddr,sizeof(sockaddr));
    
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    ret =  listen(lfd, 8);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }

    struct sockaddr_in clientaddr;
    int len = sizeof(clientaddr);
    int cfd = accept(lfd, (struct sockaddr *)&clientaddr, &len);
    if(cfd == -1) {
        perror("accept");
        exit(-1);
    }

    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientPort = ntohs(clientaddr.sin_port);
    printf("client ip: %s, port is %d\n", clientIP,clientPort);

    char recvBuf[1024] ={0};
    while(1) {
        len = read(cfd,recvBuf,sizeof(recvBuf));
        if(len == -1) {
            perror("read");
            exit(-1);
        }else if(len > 0) {
            printf("recv client data: %s\n", recvBuf);
        }else if(len == 0) {
            printf(" client disconnent");
        }

        write(cfd, "server", 7);
    }
    len = read(cfd,recvBuf,sizeof(recvBuf));
    if(len == -1) {
        perror("read");
        exit(-1);
    }else if(len > 0) {
        printf("recv client data: %s\n", recvBuf);
    }else if(len == 0) {
        printf(" client disconnent");
    }

    write(cfd, "server", 7);
    close(cfd);
    close(lfd);

    return 0;

}
