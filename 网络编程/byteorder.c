/*  
    字节序：字节在内存中存储的顺序。
    小端字节序：数据的高位字节存储在内存的高位地址，低位字节存储在内存的低位地址
    大端字节序：数据的低位字节存储在内存的高位地址，高位字节存储在内存的低位地址
*/

// 通过代码检测当前主机的字节序
#include <stdio.h>

int main() {
    // 联合体在内存中占用一块固定内存区域，同一时刻仅有一个变量有效。
    // 且大小由变量中占用字节最大的数据类型决定,切会不断被新数值刷新，旧数值便会失效。
    union {
        short value;    // 2字节
        char bytes[sizeof(short)];  // char[2]
    } test;

    test.value = 0x0102;
    if((test.bytes[0] == 1) && (test.bytes[1] == 2)) {
        printf("大端字节序\n");
    } else if((test.bytes[0] == 2) && (test.bytes[1] == 1)) {
        printf("小端字节序\n");
        test.bytes[0] = 'a';
        test.bytes[1] = 'A';
        printf("bytes[0] = %c, bytes[1] = %c, value = %d", test.bytes[0], test.bytes[1], test.value);
    } else {
        printf("未知\n");
    }

    return 0;
}