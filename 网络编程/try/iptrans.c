#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
    char buf[] = "192.168.1.4";
    unsigned int nums = 0;
    inet_pton(AF_INET, buf, &nums);
    unsigned char *p = (unsigned char *)&nums;
    printf("%d %d %d %d\n",*p,*(p+1),*(p+2),*(p+3));
    printf("======================================\n");

    char ip[16];
    const char * ans = inet_ntop(AF_INET,&nums, ip, sizeof(ip));
    

    printf("%s\n",ip);
    printf("%s\n", ans);
    printf("%lu",sizeof(void *));
    return 0;

}