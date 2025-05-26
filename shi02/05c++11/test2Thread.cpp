
#include<thread>
#include<iostream>
using namespace std;


/*
c++语言级别的多线程   =》  代码可以跨平台


线程内容：
一 怎么创建一个线程
thread定义一个线程对象。传入函数和参数

二 子线程如何结束
子线程函数运行完成线程就结束了，

三 主线程如何处理子线程
join或者detach



*/



void f1(int time){
    //睡眠5s
    this_thread::sleep_for(chrono::seconds(time));
    cout << "hello thread1" << endl;
}

int main(){
    //定义了一个线程对象，传入一个线程函数，新线程就开始运行了
    thread t1(f1,5);
    //
    //t1.join();//主线程等待子线程结束主线程再继续往下运行

    //主线程运行完成，所有子线程会自动结束
    t1.detach();//把子线程设置为分离线程
    cout << "main thread done" << endl;


    return 0;
}



