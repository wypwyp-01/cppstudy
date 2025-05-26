// ubuntu 服务器端 192.168.200.130
// 改自牛客版本服务器端  单线程版本
// poll实现
#include <poll.h>
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

    // 使用poll
    struct pollfd myfd[100]; // 存储待检测的文件描述符的集合
    nfds_t nfds = 0;
    // 先进行初始化
    for (int i = 0; i < 1024; i++)
    {
        myfd[i].fd = -1;       // 还没有被占用的元素
        myfd->events = POLLIN; // 时间都设置为POLLIN
    }

    myfd[0].fd = fd; // 用于监听的文件描述符

    while (true)
    {
        // 开始循环
        sleep(1);
        int ret = poll(myfd, nfds + 1, -1);
        if (ret < 0)
        {
            perror("poll\n");
            exit(0);
        }

        // 有文件描述符就绪
        if (myfd[0].revents & POLLIN)
        {
            // 如果监听的文件描述符
            // 建立通信文件描述符
            struct sockaddr_in acceptaddr;
            socklen_t len = sizeof(acceptaddr);
            // 这里的accept肯定不会阻塞了
            int acceptfd = accept(fd, (struct sockaddr *)&acceptaddr, &len);
            if (acceptfd == -1)
            {
                perror("accept failed\n");
                return -1;
            }
            char ip[32];
            cout << "客户端ip：" << inet_ntop(AF_INET, &acceptaddr.sin_addr.s_addr, ip, 32) << "客户端端口" << ntohs(acceptaddr.sin_port) << endl;

            // 把通信文件描述符放进去
            int i;
            for (i = 0; i < 1024; i++)
            {
                if (myfd[i].fd == -1)
                {
                    myfd[i].fd = acceptfd;
                    myfd[i].events = POLLIN;
                    break;
                }
            }
            // 更新nfds
            if (i > nfds)
            {
                nfds = i;
            }
        }
        // 检测通信的文件描述符
        for (int i = 0; i < nfds + 1; i++)
        {
            if (myfd[i].revents & POLLIN && myfd[i].fd != fd)
            {
                // 开始通信
                char buff[1024] = {0};
                int readlen = read(myfd[i].fd, buff, 1024);
                if (readlen == -1)
                {
                    perror("read failed\n");
                    exit(1);
                }
                if (readlen == 0)
                {
                    cout << "客户端断开连接" << endl;
                    close(myfd[i].fd);
                    myfd[i].fd = -1;
                }
                cout << "客户端发来的消息：" << buff << endl;

                // 发送消息
                char writebuff[1024] = "hello i am server";
                // char writebuff[1024];
                // cin.getline(writebuff,1024);
                int writelen = write(myfd[i].fd, writebuff, sizeof(writebuff));
                if (writelen == -1)
                {
                    perror("write failed\n");
                    return -1;
                }
            }
        }
    }
}