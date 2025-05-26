//ubuntu 服务器端 192.168.200.130
//改自牛客版本服务器端  单线程版本
//select实现
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    // 创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket failed\n");
        return -1;
    }
    // 绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    // 主机字节序转换成网络字节序
    inet_pton(AF_INET, "192.168.200.130", &saddr.sin_addr.s_addr);
    // saddr.sin_addr.s_addr = INADDR_ANY;
    int bindret = bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (bindret == -1)
    {
        perror("bind failed\n");
        return -1;
    }

    // 监听
    int listenret = listen(fd, 128);
    if (listenret == -1)
    {
        perror("listen failed\n");
        return -1;
    }

    // 使用select
    // 读集合
    fd_set readset;
    FD_ZERO(&readset);
    FD_SET(fd, &readset);
    fd_set tmp = readset;

    int maxfd = fd; // 表示最大得文件描述符
    // 循环调用select
    while (true)
    {
        tmp = readset;                                             // 更新tmp
        int selectret = select(maxfd + 1, &tmp, NULL, NULL, NULL); //
        // 判断是不是监听的描述符
        if (FD_ISSET(fd, &tmp))
        {
            // 如果返回值为一，说明用于监听的描述符读缓冲区有数据
            // 接受客户端的连接
            struct sockaddr_in acceptaddr;
            socklen_t len = sizeof(acceptaddr);
            int acceptfd = accept(fd,(struct sockaddr *) &acceptaddr,&len); 
            if(acceptfd == -1){
                perror("accept failed\n");
                return -1;
            }
            char ip[32];
            cout << "客户端ip：" << inet_ntop(AF_INET,&acceptaddr.sin_addr.s_addr,ip,32) << "客户端端口" << ntohs(acceptaddr.sin_port) << endl;
            FD_SET(acceptfd, &readset);            // 得到一个新的文件描述符，就放到待检测的买哦舒服里面
            // 下一轮select被调用就会检测新的添加进去的文件描述符
            // 判断要不要更新最大的文件描述符
            if (acceptfd > maxfd)
            {
                maxfd = acceptfd;
            }
        }
        // 如果不是监听描述符  就是通信描述符
        //  只有一个监听描述符  n个通信描述符
        //  判断是不是通信的描述符
        for (int i = 0; i <= maxfd; i++)
        {
            if (i != fd && FD_ISSET(i, &tmp))
            {
                // 条件都满足，说明i对应的通信文件描述符读缓冲区有数据
                // 接收数据
                char buff[1024] = {0};
                int readlen = read(i, buff, 1024);
                if (readlen == -1)
                {
                    perror("read failed\n");
                    exit(1);
                }
                if (readlen == 0)
                {
                    cout << "客户端断开连接" << endl;
                    FD_CLR(i, &readset);
                    close(i); // 关闭文件描述符
                    break;
                }
                cout << "客户端发来的消息：" << buff << endl;

                // 发送消息
                char writebuff[1024] = "hello i am server";
                //char writebuff[1024];
                //cin.getline(writebuff,1024);
                int writelen = write(i, writebuff, sizeof(writebuff));
                if (writelen == -1)
                {
                    perror("write failed\n");
                    return -1;
                }
                sleep(1);
            }
        }
    }
    // accept建立连接
    // close(acceptfd);
    close(fd);
    return 0;
}