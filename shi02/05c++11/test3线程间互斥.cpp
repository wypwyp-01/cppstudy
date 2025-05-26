

#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

int count = 100; // 有100张票，三个窗口
mutex m;
void func(int i)
{

    while (count > 0)
    {
        // m.lock();
        {
            //lock_guard<mutex> lock(m);
            unique_lock<mutex> lock(m);
            if (count > 0)
            {
                cout << "窗口" << i << "卖出第" << count << "张票" << endl;
                count--;
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }

        // m.unlock();
    }
}

int main()
{
    thread t1(func, 1);
    thread t2(func, 2);
    thread t3(func, 3);

    t1.join();
    t2.join();
    t3.join();

    cout << "所有窗口买票结束" << endl;

    return 0;
}
