

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

/*
线程间的同步通信机制


多线程编程的两个问题：
1、线程间的互斥
竞态条件 =》临界区 =>保证原子操作 =》互斥锁 或 轻量级的无锁实现
2、线程间的同步通信
生产者 消费者问题





*/
mutex m;
condition_variable c;
class Queue
{
public:
    void put(int val)
    {
        unique_lock<mutex> lock(m);
        while (!que.empty())
        {
            // 生产者应该通知消费者消费  通知完了再生产
            // 生产者应该进入阻塞状态，并把锁释放掉
            c.wait(lock);
        }
        que.push(val);
        cout << "生产者 生产 " << val << endl;

        // 线程得到通知后，就会从等待状态=》阻塞状态
        // c.notify_one();//通知一个线程  生产了一个物品
        c.notify_all(); // 通知其他所有线程，生产了一个物品
    }

    int get()
    { // 消费物品
        unique_lock<mutex> lock(m);
        while (que.empty())
        {
            // 消费者线程法线 que是空的，通知生产者线程，先生产物品
            // 消费者线程进入等待状态，把互斥锁释放掉
            c.wait(lock);
        }
        int ret = que.front();
        que.pop();
        cout << "消费者 消费" << ret << endl;
        c.notify_all(); // 通知生产者线程，消费完了
        return ret;
    }

private:
    queue<int> que;
};
Queue que;
void producer()
{
    for (int i = 0; i < 10; i++)
    {
        que.put(i + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void consumer()
{
    for (int i = 0; i < 10; i++)
    {
        que.get();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{

    thread t1(producer);
    thread t2(consumer);

    t1.join();

    t2.join();

    return 0;
}
