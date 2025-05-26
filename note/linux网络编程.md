爱编程的大丙：

[https://subingwen.cn/linux/socket/#4-1-%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%AB%AF%E9%80%9A%E4%BF%A1%E6%B5%81%E7%A8%8B](https://subingwen.cn/linux/socket/#4-1-%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%AB%AF%E9%80%9A%E4%BF%A1%E6%B5%81%E7%A8%8B)

### TCP通信流程
![](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250312202554323.png)![](https://cdn.nlark.com/yuque/0/2025/png/38380929/1741866345874-00b1369d-bd26-49d3-a090-deb5a37225e6.png)

#### 服务端：
创建用于监听的套接字, 这个套接字是一个文件描述符

```cpp
int lfd = socket();
```

将得到的监听的文件描述符和本地的IP 端口进行绑定

```plain
bind();
```

设置监听(成功之后开始监听, 监听的是客户端的连接)

```plain
listen();
```

等待并接受客户端的连接请求, 建立新的连接, 会得到一个新的文件描述符(通信的)，没有新连接请求就阻塞

这个函数是一个阻塞函数，当没有新的客户端连接请求的时候，该函数阻塞；当检测到有新的客户端连接请求时，阻塞解除，新连接就建立了，得到的返回值也是一个文件描述符，基于这个文件描述符就可以和客户端通信了。

```plain
int cfd = accept();
```

通信，读写操作默认都是阻塞的

```plain
// 接收数据
read(); / recv();
// 发送数据
write(); / send();
```

断开连接, 关闭套接字

```plain
close();
```





#### 读写函数
```cpp
ssize_t read(int sockfd, void *buf, size_t size);
ssize_t recv(int sockfd, void *buf, size_t size, int flags);
```

sockfd: 用于通信的文件描述符, accept() 函数的返回值 
buf: 指向一块有效内存, 用于存储接收是数据 
size: 参数buf指向的内存的容量 
flags: 特殊的属性, 一般不使用, 指定为 0 
返回值: 
大于0：实际接收的字节数 
等于0：对方断开了连接 
-1：接收数据失败了



### 五种IO模型
#### 阻塞IO
当⽤户程序执⾏ read ，线程会被阻塞，⼀直等到内核数据准备好，并把数据从内核缓冲区拷⻉到应⽤程序的缓冲区中，当拷⻉过程完成， read 才会返回。

注意，**阻塞等待的是「内核数据准备好」和「数据从内核态拷⻉到⽤户态」这两个过程**。过程如下图：

![image-20250516114513810](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516114513810.png)





#### 非阻塞IO
⾮阻塞的 read 请求在数据未准备好的情况下⽴即返回，可以继续往下执⾏，此时应⽤程序不断轮询内核，直到数据准备好，内核将数据拷⻉到应⽤程序缓冲区， read 调⽤才可以获取到结果。

![image-20250516115838092](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516115838092.png)

**这⾥最后⼀次 read 调⽤，获取数据的过程，是⼀个同步的过程，是需要等待的过程。这⾥的同步指的是内核态的数据拷⻉到⽤户程序的缓存区这个过程。**





#### IO多路复用
多个IO注册到⼀个进程上，没有数据可读时，select进⾏被阻塞，数据到来时候select返回，进⾏数据拷⻉

I/O复用模型允许单个线程监视多个文件描述符（如套接字），以确定它们是否有数据可读、可写或是否有异常。

![image-20250516120205539](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516120205539.png)



⽆论是阻塞 I/O、⾮阻塞 I/O，还是基于⾮阻塞 I/O 的多路复⽤**都是同步调⽤。因为它们在** **read**

**调⽤时，内核将数据从内核空间拷⻉到应⽤程序空间，过程都是需要等待的，也就是说这个过程是同步**

**的，如果内核实现的拷⻉效率不⾼，****read** **调⽤就会在这个同步过程中等待⽐较⻓的时间。**



#### 信号驱动式 IO
<font style="color:rgb(31,35,41);">向内核注册⼀个信号处理函数，进程不阻塞，</font>让内核在描述符就绪时发送信号通知。（通知何时可以启动 IO 操作）

![](https://cdn.nlark.com/yuque/0/2025/png/38380929/1742042928358-fcf6327d-7022-4c3b-b984-48c84f0f53aa.png)

#### 异步 IO

真正的**异步** **I/O** 是「内核数据准备好」和「数据从内核态拷⻉到⽤户态」这两个过程都不⽤等待。

当我们发起 aio_read 之后，**就⽴即返回，内核⾃动将数据从内核空间拷⻉到应⽤程序空间**，这个拷⻉过

程同样是异步的，内核⾃动完成的，和前⾯的同步操作不⼀样，应⽤程序并不需要主动发起拷⻉动作。过

程如下图：

![image-20250516120502620](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516120502620.png)

#### 同步 IO 异步 IO
+ <font style="color:rgb(85, 85, 85);">同步（阻塞）I/O：在一个线程中，CPU执行代码的速度极快，然而，一旦遇到IO操作，如读写文件、发送网络数据时，就需要等待IO操作完成，才能继续进行下一步操作。这种情况称为同步IO。</font>
+ <font style="color:rgb(85, 85, 85);">异步（非阻塞）I/O：当代码需要执行一个耗时的IO操作时，它只发出IO指令，并不等待IO结果，然后就去执行其他代码了。一段时间后，当IO返回结果时，再通知CPU进行处理。</font>



### IO 多路复用
<font style="color:rgb(31,35,41);">IO多路复⽤？ </font>

<font style="color:rgb(31,35,41);">⼀个进程可以监视多个描述符，同时处理多个IO请求，使⽤select、poll、epoll函数，谁的数据到达就处理谁的请求 </font>

<font style="color:rgb(31,35,41);">多路：监听多个socket⽹络连接 </font>

<font style="color:rgb(31,35,41);">复⽤：复⽤同⼀个线程</font>

<font style="color:rgb(31,35,41);">优点： </font>

<font style="color:rgb(31,35,41);">只需要⼀个进程就可以处理多个事件，数据共享容易、调试容易 </font>

<font style="color:rgb(31,35,41);">单⼀进程中，不需要进程线程切换的开销 </font>

<font style="color:rgb(31,35,41);">缺点： </font>

<font style="color:rgb(31,35,41);">逻辑困难 </font>

<font style="color:rgb(31,35,41);">不能充分利⽤多核处理器</font>

### select
函数原型：

```plain
int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval * timeout);
```

执行流程：

+ ⽤⼾线程调⽤select，将fd_set从⽤⼾空间拷⻉到内核空间
+ 内核在内核空间对fd_set遍历⼀遍，检查是否有就绪的socket描述符，如果没有的话，就会进⼊休眠，直到有就绪的socket描述符
+ 内核返回select的结果给⽤⼾线程，即就绪的⽂件描述符数量
+ ⽤⼾拿到就绪⽂件描述符数量后，再次对fd_set进⾏遍历，找出就绪的⽂件描述符
+ ⽤⼾线程对就绪的⽂件描述符进⾏读写操作



细节：

select()函数中第2、3、4个参数都是fd_set类型，它表示一个文件描述符的集合，类似于信号集 sigset_t，这个类型的数据有128个字节，也就是**1024**个标志位，和内核中文件描述符表中的文件描述符个数是一样的。**这意味着 **`select`** 一次最多可以监视1024个文件描述符。**

fd_set中存储了要委托内核检测读缓冲区的文件描述符集合。

如果集合中的标志位为0代表不检测这个文件描述符状态  
如果集合中的标志位为1代表检测这个文件描述符状态

![](https://subingwen.cn/linux/select/image-20210324233252448.png)

内核在遍历这个读集合的过程中，如果被检测的文件描述符对应的读缓冲区中没有数据，内核将修改这个文件描述符在读集合`fd_set`中对应的标志位，改为`0`，如果有数据那么这个标志位的值不变，还是`1`。

![](https://subingwen.cn/linux/select/image-20210324234324388.png)

当`select()`函数解除阻塞之后，被内核修改过的读集合通过参数传出，此时集合中只要标志位的值为`1`，那么它对应的文件描述符肯定是就绪的，我们就可以基于这个文件描述符和客户端建立新连接或者通信了。



select缺点：

+ 待检测集合（第2、3、4个参数）需要频繁的在用户区和内核区之间进行数据的<font style="color:#DF2A3F;">拷贝</font>，效率低
+ 内核对于select传递进来的待检测集合的检测方式是线性的
+ select 只返回就绪文件的个数，具体哪个文件描述符就绪了<font style="color:#DF2A3F;">还需要遍历  模糊通知</font>
+ 可以检测的文件描述符的数量有限制



### poll
poll与select的相同和区别

相同：

内核对应文件描述符的<font style="color:#DF2A3F;">检测也是以线性</font>的方式进行轮询，根据描述符的状态进行处理

poll和select检测的文件描述符集合会在检测过程中<font style="color:#DF2A3F;">频繁的进行用户区和内核区的拷贝</font>，它的开销随着文件描述符数量的增加而线性增大，从而效率也会越来越低。





区别：

select检测的文件描述符个数上限是1024，poll<font style="color:#DF2A3F;">没有最大文件描述符数量的限制（基于链表）</font>  
select可以跨平台使用，poll<font style="color:#DF2A3F;">只能在Linux平台使用</font>





[select pool epoll](https://zhuanlan.zhihu.com/p/367591714)

[另一篇文章](https://zhuanlan.zhihu.com/p/554348972)

[IO多路转接（复用）之epoll](https://subingwen.cn/linux/epoll/#2-%E6%93%8D%E4%BD%9C%E5%87%BD%E6%95%B0)

### epoll
#### epoll 特点
<font style="color:#DF2A3F;">不拷贝 明确通知</font>



对于待检测集合select和poll是基于线性方式处理的，epoll是基于红黑树来管理待检测集合的。  <font style="color:#DF2A3F;">红黑树</font>

select和poll每次都会线性扫描整个待检测集合，集合越大速度越慢，epoll使用的是回调机制，效率高，处理效率也不会随着检测集合的变大而下降

select和poll工作过程中存在内核/用户空间数据的频繁拷贝问题，在epoll中内核和用户区使用的是共享内存（基于mmap内存映射区实现），省去了不必要的内存拷贝。  <font style="color:#DF2A3F;">不拷贝</font>

程序猿需要对select和poll返回的集合进行判断才能知道哪些文件描述符是就绪的，通过epoll可以直接得到已就绪的文件描述符集合，无需再次检测   <font style="color:#DF2A3F;">明确通知</font>

使用epoll没有最大文件描述符的限制，仅受系统中进程能打开的最大文件数目限制  <font style="color:#DF2A3F;">文件描述符数量无限制</font>



#### 三个函数
```basic
int epoll_create(int size);
```

函数参数 size：在Linux内核2.6.8版本以后，这个参数是被忽略的，只需要指定一个大于0的数值就可以了。

函数返回值：

失败：返回-1

成功：返回一个有效的文件描述符，通过这个文件描述符就可以访问创建的epoll实例了



```basic
// 联合体, 多个变量共用同一块内存        
typedef union epoll_data {
 	void        *ptr;
	int          fd;	// 通常情况下使用这个成员, 和epoll_ctl的第三个参数相同即可
	uint32_t     u32;
	uint64_t     u64;
} epoll_data_t;

struct epoll_event {
	uint32_t     events;      /* Epoll events */
	epoll_data_t data;        /* User data variable */
};
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

epfd：epoll_create() 函数的返回值，通过这个参数找到epoll实例

op：这是一个枚举值，控制通过该函数执行什么操作

EPOLL_CTL_ADD：往epoll模型中添加新的节点

EPOLL_CTL_MOD：修改epoll模型中已经存在的节点

EPOLL_CTL_DEL：删除epoll模型中的指定的节点

fd：文件描述符，即要添加/修改/删除的文件描述符

event：epoll事件，用来修饰第三个参数对应的文件描述符的，指定检测这个文件描述符的什么事件

events：委托epoll检测的事件

EPOLLIN：读事件, 接收数据, 检测读缓冲区，如果有数据该文件描述符就绪

EPOLLOUT：写事件, 发送数据, 检测写缓冲区，如果可写该文件描述符就绪

EPOLLERR：异常事件

data：用户数据变量，这是一个联合体类型，通常情况下使用里边的fd成员，用于存储待检测的文件描述符的值，在调用epoll_wait()函数的时候这个值会被传出。

函数返回值：

失败：返回-1

成功：返回0



```basic
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
```

epfd：epoll_create() 函数的返回值, 通过这个参数找到epoll实例

events：传出参数, 这是一个结构体数组的地址, 里边存储了已就绪的文件描述符的信息

maxevents：修饰第二个参数, 结构体数组的容量（元素个数）

timeout：如果检测的epoll实例中没有已就绪的文件描述符，该函数阻塞的时长, 单位ms 毫秒

0：函数不阻塞，不管epoll实例中有没有就绪的文件描述符，函数被调用后都直接返回

大于0：如果epoll实例中没有已就绪的文件描述符，函数阻塞对应的毫秒数再返回

-1：函数一直阻塞，直到epoll实例中有已就绪的文件描述符之后才解除阻塞

函数返回值：

成功：

等于0：函数是阻塞被强制解除了, 没有检测到满足条件的文件描述符

大于0：检测到的已就绪的文件描述符的总个数





#### epoll 的实现
[epoll的讲解比较详细](https://zhuanlan.zhihu.com/p/667047565)

+ <font style="color:rgb(25, 27, 31);">epoll_create 创建 eventpoll对象（红黑树，双链表）</font>
+ <font style="color:#DF2A3F;">一棵红黑树</font><font style="color:rgb(25, 27, 31);">，存储监听的所有文件描述符，并且通过 epoll_ctl 将文件描述符添加、删除到红黑树</font>
+ <font style="color:#DF2A3F;">一个双链表</font><font style="color:rgb(25, 27, 31);">，存储就绪的文件描述符列表，epoll_wait调用时，检测此链表中是否有数据，有的话直接返回</font>
+ <font style="color:rgb(25, 27, 31);">所有添加到 eventpoll 中的事件都与设备驱动程序建立回调关系</font>

<font style="color:rgb(6, 6, 7);"></font>

+ <font style="color:rgb(6, 6, 7);">当文件描述符上的事件发生时（如数据到达、可写等），内核会将该事件添加到 </font>`epoll`<font style="color:rgb(6, 6, 7);"> 实例的就绪列表中。这种通知机制是内核驱动的，不需要用户空间的程序不断轮询检查。</font>
+ epoll_wait 的作用：当用户空间调用 epoll_wait 时，它简单地从就绪列表中检索已经就绪的事件，而不是进行轮询检查。如果没有事件就绪，epoll_wait 可以阻塞等待，直到超时或有事件发生。





eventpool 的详细讲解：













#### epoll 的两种触发模式
LT 模式

只要文件描述符（fd）处于可读或可写状态，事件就会一直触发。<font style="color:rgb(31,35,41);">如果没有⽴即处理，会持续通知，直到处理</font>

LT是阻塞模式或者⾮阻塞模式都可以

LT不会丢失数据或消息



ET 模式

只有当文件描述符的状态从不可读/不可写变为可读/可写时才会触发事件。（当文件描述符从未就绪变为就绪时）

ET必须是⾮阻塞模式

epoll的边沿模式下 epoll_wait()检测到<font style="color:#DF2A3F;">文件描述符有新事件才会通知</font>，如果不是新的事件就不通知，通知的次数比水平模式少，效率比水平模式要高。

缺点：每次读写事件必须保证把数据读写完，否则第⼆次可读的时候才会通知，造成积压





<font style="color:#DF2A3F;">ET 模式必须对用于通信的文件描述符设置非阻塞</font>

默认情况下套接字通信处理流程是阻塞的。当循环接收客户端发过来的数据，接受完了之后，当缓冲区中没有数据时，read 或 recv 会阻塞等待数据到来。整个程序就直接停止在这里了。







<font style="color:#DF2A3F;">！！！有时间试验一下：在 LT  + 阻塞模式 + 单线程    下使用 while 循环接收数据，阻塞在一个文件描述符的缓冲区之后，还能不能接受其他文件描述符的数据？</font>



在阻塞模式下，缓冲区没数据：

+ `**read()**`** 调用会阻塞，直到有数据到达**（或者发生错误/连接关闭）。
+ 线程会**挂起等待数据**，直到缓冲区有数据可读。

在非阻塞模式下，缓冲区没数据：

 如果**缓冲区无数据**，返回 `-1`，并设置 `errno = EAGAIN` 或 `EWOULDBLOCK`，表示当前没有可读数据。  

所以判断一下错误号就可以知道缓冲区没数据了，就结束循环。

```cpp
if(errno == EAGAIN){
                            //在返回值为-1的时候，如果错误号等于-1，
                            //说明数据已经读完了，这个时候应该退出循环，而不是直接结束程序
                            cout << "数据接收完毕" << endl;
                            break;
                        }
```



####  什么时候用 select，什么时候用epoll  
`epoll` 更适用于高并发场景，而select 适用于少量连接 或 跨平台兼容性要求较高** 的情况。  



#### 什么时候用 LT，什么时候用 ET
+ **低并发、小型应用**（如普通 HTTP 服务器）：**用 LT，简单可靠**。数据量较小（单次触发足以读取数据）
+ **高并发、大吞吐量服务器**（如 Nginx）：**用 ET，提高性能**，但需要小心数据丢失。数据量大（减少触发次数），对性能要求高。



#### 惊群效应，C10K   C1000K





### Linux系统是如何收发网络包的？

#### 接收网络包的流程

当⽹卡接收到⼀个⽹络包后，会通过 DMA 技术，将⽹络包放⼊到 Ring Buffer，这个是⼀个环形缓冲区。

然后触发中断，告诉操作系统。

操作系统 将数据拷贝到内核缓冲区，从⽽可以作为⼀个⽹络包交给⽹络协议栈进⾏逐层处理。



⾸先，会先进⼊到⽹络接⼝层，在这⼀层会检查报⽂的合法性，如果不合法则丢弃，**合法则会找出该⽹络包的上层协议的类型，⽐如是 IPv4，还是 IPv6，接着再去掉帧头和帧尾，然后交给⽹络层。**



到了⽹络层，则取出 IP 包，判断⽹络包下⼀步的⾛向，⽐如是交给上层处理还是转发出去。当确认这个⽹络包要发送给本机后，就会从 **IP 头⾥看看上⼀层协议的类型是 TCP 还是 UDP，接着去掉 IP 头，然后交给传输层。**



传输层取出 TCP 头或 UDP 头，**根据四元组「源 IP、源端⼝、⽬的 IP、⽬的端⼝」 作为标识，找出对应的 Socket，并把数据拷⻉到 Socket 的接收缓冲区。**



应⽤层程序调⽤ Socket 接⼝，**从内核的 Socket 接收缓冲区读取新到来的数据到应⽤层。**



#### 发送网络包的流程

⾸先，应⽤程序会调⽤ Socket 发送数据包的接⼝，由于这个是系统调⽤，所以会从⽤户态陷⼊到内核态中 的 Socket 层，**Socket 层会将应⽤层数据拷⻉到 Socket 发送缓冲区中。** 

**接下来，⽹络协议栈从 Socket 发送缓冲区中取出数据包，并按照 TCP/IP 协议栈从上到下逐层处理。**

 **如果使⽤的是 TCP 传输协议发送数据，那么会在传输层增加 TCP 包头，然后交给⽹络层，⽹络层会给数 据包增加 IP 包，然后通过查询路由表确认下⼀跳的 IP，并按照 MTU ⼤⼩进⾏分⽚。** 

分⽚后的⽹络包，就会被送到⽹络接⼝层，**在这⾥会通过 ARP 协议获得下⼀跳的 MAC 地址，然后增加帧 头和帧尾，放到发包队列中。**

这⼀些准备好后，会触发软中断告诉⽹卡驱动程序，这⾥有新的⽹络包需要发送，**最后驱动程序通过  DMA，从发包队列中读取⽹络包，将其放⼊到硬件⽹卡的队列中，随后物理⽹卡再将它发送出去。**

<img src="C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516141826867.png" alt="image-20250516141826867"  />





### 零拷贝

#### 为什么要有DMA技术

没有DMA之前的IO过程：整个数据的传输过程，都要需要 CPU 亲⾃参与搬运数据的过程，⽽且这个过程，CPU 是不能 做其他事情的。

传输大量数据的时候，CPU忙不过来。所以发明了DMA



**在进⾏ I/O 设备和内存的数据传输的时候，数据搬运的⼯作全部交给  DMA 控制器，⽽ CPU 不再参与任何与数据搬运相关的事情，这样 CPU 就可以去处理别的事务。**

整个数据传输的过程，CPU 不再参与数据搬运的⼯作，⽽是全程由 DMA 完成，**但是 CPU 在 这个过程中也是必不可少的，因为传输什么数据，从哪⾥传输到哪⾥，都需要 CPU 来告诉 DMA 控制器。**



#### 传统的文件传输

**四次上下文切换+四次数据拷贝**

![image-20250516155556892](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516155556892.png)

**想要提高文件传输的性能，就要减少“用户态与内核态的上下文切换”和“内存拷贝”的次数。**



#### 如何实现零拷贝



##### mmap+write

mmap() 系统调⽤函数会直接**把内核缓冲区⾥的数据「映射」到⽤户空间**，这样，操作系统内核与⽤户空 间就不需要再进⾏任何的数据拷⻉操作。

![image-20250516160141612](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516160141612.png)

应⽤进程调⽤了  mmap() 后，DMA 会把磁盘的数据拷⻉到内核的缓冲区⾥。

接着，应⽤进程跟操作 系统内核「共享」这个缓冲区； 应⽤进程再调⽤  write() ，操作系统直接将内核缓冲区的数据拷⻉到 socket 缓冲区中，这⼀切都发⽣ 在内核态，由 CPU 来搬运数据； 

最后，把内核的 socket 缓冲区⾥的数据，拷⻉到⽹卡的缓冲区⾥，这个过程是由 DMA 搬运的。



**减少了一次数据拷贝的过程**



##### sendfile

它**可以替代前⾯的  read() 和  write() 这两个系统调⽤，这样就可以减少⼀次系统调⽤**，也就减少 了 2 次上下⽂切换的开销。

其次，该系统调⽤，**可以直接把内核缓冲区⾥的数据拷⻉到 socket 缓冲区⾥，不再拷⻉到⽤户态，**这样就 只有 2 次上下⽂切换，和 3 次数据拷⻉。

![image-20250516164346298](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516164346298.png)



如果⽹卡⽀持 **SG-DMA 技术（和普通的 DMA 有所不同），我们可以进⼀步减少通过 CPU 把内核缓冲区⾥的数据拷⻉到 socket  缓冲区的过程。**

第⼀步，通过 DMA 将磁盘上的数据拷⻉到内核缓冲区⾥； sendfile() 系统调

第⼆步，缓冲区描述符和数据⻓度传到 socket 缓冲区，这样⽹卡的 SG-DMA 控制器就可以直接将内 核缓存中的数据拷⻉到⽹卡的缓冲区⾥，此过程不需要将数据从操作系统内核缓冲区拷⻉到 socket  缓冲区中，这样就减少了⼀次数据拷⻉；

![image-20250516164642709](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250516164642709.png)

这就是所谓的**零拷⻉（Zero-copy）技术，因为我们没有在内存层⾯去拷⻉数据，也就是说全程没有通过  CPU 来搬运数据，所有的数据都是通过 DMA 来进⾏传输的。**

零拷⻉技术的⽂件传输⽅式相⽐传统⽂件传输的⽅式，**减少了 2 次上下⽂切换和数据拷⻉次数，只需要 2  次上下⽂切换和数据拷⻉次数，就可以完成⽂件的传输，⽽且 2 次的数据拷⻉过程，都不需要通过 CPU， 2 次都是由 DMA 来搬运。**



#### pagecache有什么作用







#### 大文件传输通什么方式实现










### reactor 模式和 PROACTOR 模式
Reactor模式：要求主线程（I/O处理单元）只负责监听文件描述符上是否有事件发生（可读、可写），若有，则立即通知工作线程（逻辑单元），将socket可读可写事件放入请求队列，交给工作线程处理。（事件分发器 事件处理器 时间循环）

Proactor模式：Proactor模式是一种基于异步I/O操作的设计模式。将所有的I/O操作都交给内核来处理（进行读、写），并在I/O操作完成后通知应用程序。工作线程仅负责处理逻辑（对报文的解析和响应），（主线程 工作线程 异步 IO 机制）



































