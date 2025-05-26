// ubuntu 服务器端 192.168.200.130
// 改自牛客版本服务器端  多线程版本
// select实现
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <pthread.h>
// #include<unistd.h>
// #include<ctime>
using namespace std;
pthread_mutex_t lock;
struct fdinfo
{
    int fd;
    int *maxfd;
    fd_set *rdset;
};
struct communciationargs
{
    // 文件描述符
    int fd;
    fd_set *rdset;
};
void *communciation(void *args)
{
    cout << "begin communication" << endl;
    communciationargs *info = (communciationargs *)args;

    char buff[1024] = {0};
    int readlen = read(info->fd, buff, 1024);
    if (readlen == -1)
    {
        perror("read failed\n");
        exit(1);
    }
    if (readlen == 0)
    {
        cout << "客户端断开连接" << endl;
        pthread_mutex_lock(&lock);
        FD_CLR(info->fd, info->rdset);
        pthread_mutex_unlock(&lock);
        close(info->fd); // 关闭文件描述符
        delete info;
        return NULL;
    }
    cout << "客户端发来的消息：" << buff << endl;

    // 发送消息
    char writebuff[1024] = "hello i am server";
    cout << "send..." << endl;
    // char writebuff[1024];
    // cin.getline(writebuff,1024);
    int writelen = write(info->fd, writebuff, sizeof(writebuff));
    if (writelen == -1)
    {
        perror("write failed\n");
        delete info;
        return NULL;
    }
    // sleep(1);
    delete info;
    return NULL;
}

void *acceptconn(void *args)
{
    // 和客户端建立连接
    fdinfo *info = (fdinfo *)args;

    struct sockaddr_in acceptaddr;
    socklen_t len = sizeof(acceptaddr);
    int acceptfd = accept(info->fd, (struct sockaddr *)&acceptaddr, &len);
    if (acceptfd == -1)
    {
        perror("accept failed\n");
        delete info;
        return NULL;
    }
    char ip[32];
    cout << "客户端ip：" << inet_ntop(AF_INET, &acceptaddr.sin_addr.s_addr, ip, 32) << "客户端端口" << ntohs(acceptaddr.sin_port) << endl;
    pthread_mutex_lock(&lock);
    FD_SET(acceptfd, info->rdset); // 得到一个新的文件描述符，就放到待检测的读集合里面
    // 下一轮select被调用就会检测新的添加进去的文件描述符
    // 判断要不要更新最大的文件描述符
    if (acceptfd > *(info->maxfd))
    {
        cout << *(info->maxfd) << " " << acceptfd << endl;
        *(info->maxfd) = acceptfd;
        cout << *(info->maxfd) << " " << acceptfd << endl;
    }
    pthread_mutex_unlock(&lock);
    cout << "end connect" << endl;
    //delete info;
    return NULL;
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    //  创建套接字
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
    //struct timeval timeout;
    //timeout.tv_sec = 10;  // 每秒超时
    //timeout.tv_usec = 0;
    while (true)
    {
        //sleep(1);
        //cout << "11111" << endl;
        pthread_mutex_lock(&lock);
        tmp = readset; // 更新tmp
        pthread_mutex_unlock(&lock);
        int selectret = select(maxfd + 1, &tmp, NULL, NULL, NULL); //
        // 判断是不是监听的描述符
        if (FD_ISSET(fd, &tmp))
        {
            // 如果返回值为一，说明用于监听的描述符读缓冲区有数据
            // 创建子线程接受客户端的连接
            // 这时候 子线程创建连接不会阻塞
            pthread_t pid;
            fdinfo *info;
            info = new fdinfo;
            info->maxfd = &maxfd;
            info->rdset = &readset;
            info->fd = fd;
            pthread_create(&pid, NULL, acceptconn, (void *)info);
            pthread_detach(pid);
        }
        // 如果不是监听描述符  就是通信描述符
        //  只有一个监听描述符  n个通信描述符
        //  判断是不是通信的描述符
        cout << "maxfd = " << maxfd << endl;
        sleep(1);
        for (int i = 0; i <= maxfd; i++)
        {
            if (i != fd && FD_ISSET(i, &tmp))
            {
                cout << "i = " << i << endl;
                // 条件都满足，说明i对应的通信文件描述符读缓冲区有数据
                // 创建一个新线程并进行通信
                communciationargs *infr;
                infr = new communciationargs;
                infr->fd = i;
                infr->rdset = &readset;
                pthread_t pid;
                cout << "begin create thread" << endl;
                int ret = pthread_create(&pid, NULL, communciation, (void *)infr);
                if (ret != 0)
                {
                    perror("thread create failed\n");
                    delete infr;
                    continue;
                }
                pthread_detach(pid);
            }
        }
    }
    // accept建立连接
    // close(acceptfd);
    close(fd);
    pthread_mutex_destroy(&lock);
    return 0;
}
