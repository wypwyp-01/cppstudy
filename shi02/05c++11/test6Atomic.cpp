#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <list>
#include <atomic>

using namespace std;
/*
互斥锁是比较重的，如果临界区代码做的事情稍稍复杂，互斥锁是值得的
但是如果是简单的++  --，用CAS来保证上面的++  --操作就足够了
*/
atomic<int> a = 0;//结果是1000
//int a = 0;//结果不是100   （971）
list<std::thread> threadlist;
void task()
{
    for (int i = 0; i < 100; i++){
        a++;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}
int main()
{

    for (int i = 0; i < 10; i++)
    {
        threadlist.push_back(thread(task));
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (auto &thr : threadlist)
    {
        thr.join();
    }

    cout << a << endl;

    return 0;
}
