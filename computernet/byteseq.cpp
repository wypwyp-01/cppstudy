#include<iostream>
#include<arpa/inet.h>
using namespace std;
/*
    字节序：字节在内存中存储的顺序
    大端字节序：数据的高位存储在内存的低位
    小段字节序：数据的高位存储在内存的高位

*/
int main(){
    //判断大端还是小端
    union{
        short value;
        char bytes[sizeof(short)];
    }tst;
    tst.value = 0x0102;
    cout << (void *)&tst.bytes[0] << ":" << (int)tst.bytes[0] << endl;
    cout << (void *)&tst.bytes[1] << ":" << (int)tst.bytes[1] << endl;

    //字节序转换函数
    short port = 9999;
    cout << htons(port) << endl;
    printf("%04x,%04x\n",port,htons(port));

    
    return 0;
}

