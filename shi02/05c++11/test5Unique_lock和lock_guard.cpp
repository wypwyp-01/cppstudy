
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;


/*
1 lock_guard和unique_lock
lock_guard只提供了构造以及析构函数，把左值引用拷贝构造和赋值运算符都删掉了，
不能用于函数的传递和返回，只能用于简单的临界区代码段中

unique_lock提供了lock以及unlock和右值引用的拷贝构造和赋值运算，
不仅可以使用在简单的临界区代码段中，还能用于函数的参数和传递。
可以和condition_variable配合使用，适合用于复杂的场景


2 condition_variable   wait和notify_all
通知在c上等待的线程，条件成立了，起来干活了。
其他在c上等到的线程，收到通知，从等待状态=》阻塞状态=》获取到互斥锁=》线程继续运行

*/

int main(){
    //lock_guard<mutex>
    //unique_lock<mutex>
    return 0;
}
