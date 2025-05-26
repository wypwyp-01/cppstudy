// ubuntu 服务器端 192.168.200.130
// 改自牛客版本服务器端
// epoll实现  单线程版本
// 边沿触发模式
// 非阻塞IO
//边沿模式  肯定是非阻塞的
//非阻塞 1 需要设置 2 需要对错误号为EAGAIN做特殊处理 3 需要把read写到循环里面

#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
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

    // 使用epoll
    int ret = epoll_create(1);
    if (ret == -1)
    {
        perror("epoll failed\n");
        exit(0);
    }
    // 添加事件
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET; // 检测fd读读缓冲区是否有数据
    ev.data.fd = fd;
    int epollctlret = epoll_ctl(ret, EPOLL_CTL_ADD, fd, &ev);

    // 检测添加的文件描述符是否就绪？
    struct epoll_event ecarray[1024];
    while (true)
    {
        //等待事件发生
        int num = epoll_wait(ret, ecarray, 1024, -1);

        // 返回值是就绪文件描述符的个数
        cout << "num = " << num << endl;
        for (int i = 0; i < num; i++)
        {
            if (ecarray[i].data.fd == fd)
            {
                // 说明是监听文件描述符
                //  建立通信文件描述符
                struct sockaddr_in acceptaddr;
                socklen_t len = sizeof(acceptaddr);
                // 这里的accept肯定不会阻塞了
                int acceptfd = accept(fd, (struct sockaddr *)&acceptaddr, &len);
                // 设置非阻塞
                int flag = fcntl(acceptfd, F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(acceptfd, F_SETFL, flag);

                if (acceptfd == -1)
                {
                    perror("accept failed\n");
                    return -1;
                }
                char ip[32];
                cout << "客户端ip：" << inet_ntop(AF_INET, &acceptaddr.sin_addr.s_addr, ip, 32) << "客户端端口" << ntohs(acceptaddr.sin_port) << endl;
                // 把得到的用于通信的文件描述符放到epoll里面

                ev.events = EPOLLIN | EPOLLET; // 检测fd读读缓冲区是否有数据
                ev.data.fd = acceptfd;
                int epollctlret = epoll_ctl(ret,
                                            EPOLL_CTL_ADD, acceptfd, &ev);
            }
            else
            {
                // 不是用于监听的  就是用于通信的文件描述符
                // 开始通信流程
                char buff[6] = {0};
                // 因为是边沿触发 所以接收数据要放在循环里面
                while (true)
                {

                    int size = sizeof(buff) / sizeof(buff[0]);
                    int readlen = read(ecarray[i].data.fd, buff, sizeof(buff) - 1);
                    if (readlen == -1)
                    {
                        if(errno == EAGAIN){
                            //在返回值为-1的时候，如果错误号等于-1，
                            //说明数据已经读完了，这个时候应该退出循环，而不是直接结束程序
                            cout << "数据接收完毕" << endl;
                            break;
                        }
                        else{
                            //如果不是EAGAIN 说明确实是调用失败了，退出
                            perror("read failed\n");
                            exit(1);
                        }
                        
                    }
                    if (readlen == 0)
                    {
                        cout << "客户端断开连接" << endl;
                        // 删除文件描述符
                        int epollctlret = epoll_ctl(ret, EPOLL_CTL_DEL, ecarray[i].data.fd, NULL); // 删除  不需要指定事件
                        close(ecarray[i].data.fd);
                        // 要先删除 再关闭  如果先关闭 再删除   会删除失败
                        break;
                    }
                    buff[readlen] = '\0';
                    cout << "客户端发来的消息：" << buff << endl;

                    // 发送消息
                    // char writebuff[1024] = "hello i am server";
                    //小写转大写
                    char writebuff[1024];
                    for (int i = 0; i < size; i++)
                    {
                        writebuff[i] = toupper(buff[i]);
                    }
                    // cin.getline(writebuff,1024);
                    int writelen = write(ecarray[i].data.fd, writebuff, sizeof(writebuff));
                    if (writelen == -1)
                    {
                        perror("write failed\n");
                        // exit(0);
                    }
                }
            }
        }
    }
    close(fd);
    return 0;
}