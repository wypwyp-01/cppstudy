// ubuntu 服务器端 192.168.200.130
// 牛客版本服务器端   单线程版本
#include<iostream>
#include<unistd.h>
#include<arpa/inet.h>

using namespace std;

int main(){
    //创建套接字
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("socket failed\n");
        return -1;
    }
    //绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    //主机字节序转换成网络字节序
    inet_pton(AF_INET,"192.168.200.130",&saddr.sin_addr.s_addr);
    //saddr.sin_addr.s_addr = INADDR_ANY;
    int bindret = bind(fd,(struct sockaddr *)&saddr,sizeof(saddr));
    if(bindret == -1){
        perror("bind failed\n");
        return -1;
    }

    //监听
    int listenret = listen(fd,128);
    if(listenret == -1){
        perror("listen failed\n");
        return -1;
    }

    //accept建立连接
    struct sockaddr_in acceptaddr;
    socklen_t len = sizeof(acceptaddr);
    int acceptfd = accept(fd,(struct sockaddr *) &acceptaddr,&len);
    if(acceptfd == -1){
        perror("accept failed\n");
        return -1;
    }
    char ip[32];
    cout << "客户端ip：" << inet_ntop(AF_INET,&acceptaddr.sin_addr.s_addr,ip,32) << "客户端端口" << ntohs(acceptaddr.sin_port) << endl;
    
    while(true){
        char buff[1024] = {0};
        int readlen = read(acceptfd,buff,1024);
        if(readlen == -1){
            perror("read failed\n");
            return -1;
        }
        if(readlen == 0){
            cout << "客户端断开连接" << endl;
            break;
        }
        cout << "客户端发来的消息：" << buff << endl;

        //发送消息
        char writebuff[1024] = "hello i am server";
        int writelen = write(acceptfd,writebuff,sizeof(writebuff));
        if(writelen == -1){
            perror("write failed\n");
            return -1;
        }
        sleep(1);
    }
    close(acceptfd);
    close(fd);    
    
    return 0;
}
