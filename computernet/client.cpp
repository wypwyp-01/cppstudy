#include<iostream>
#include<arpa/inet.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>
using namespace std;

int main(){
    //创建通信套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        perror("create socket failed\n");
        return -1;
    }
    //和本地端口进行绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);//端口
    inet_pton(AF_INET,"192.168.200.131",&saddr.sin_addr.s_addr);
    
    int ret = connect(fd,(struct sockaddr *) &saddr,sizeof(saddr));
    if(ret == -1){
        perror("connect failed\n");
        return -1;
    }
    //通信
    int number = 0;
     while(true){
         char buf[1024];
         sprintf(buf,"hello,world,%d...\n",number++);
         send(fd, buf, strlen(buf) + 1, 0);

        //接收数据
        memset(buf,0,sizeof(buf));
        int len = recv(fd,buf,sizeof(buf),0);
         if(len > 0){
             cout << "server say:" << buf << endl;  
         }
         else if(len == 0){
             cout << "服务器断开连接" << endl;
             break;
         }
         else{
             perror("recv failed\n");
             break;
         }
         sleep(1);
     }

     close(fd);
     return 0;
}
