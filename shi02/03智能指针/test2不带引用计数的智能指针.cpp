
#include <boost/scoped_ptr.hpp>
#include <memory>
#include <iostream>
using namespace std;

/*
裸指针  需要手动释放  否则可能造成内存泄漏
可能忘了手动释放，
或者写了手动释放的逻辑，但是由于程序的逻辑执行顺序和预想的不一样，导致手动释放资源的代码没有运行到

智能指针：能做到资源的自动释放
利用 栈上的对象出作用域自动析构的特征，来做到资源的自动释放

智能指针能否定义到堆上？不能
*/
class Test
{
public:
    Test() {}
    void test()
    {
        cout << "call Test::test()" << endl;
    }

private:
};

template <class T>
class SmartPtr
{
public:
    SmartPtr(T *ptr = nullptr) : m_ptr(ptr) {}
    ~SmartPtr()
    {
        cout << "~SmartPtr()" << endl;
        if (m_ptr)
            delete m_ptr;
    }

    T &operator*() { return *m_ptr; }

    T *operator->() { return m_ptr; }

private:
    T *m_ptr;
};

/*
不带引用计数的智能指针
auto_ptr

scoped_ptr
unique_ptr
*/

int main()
{

    // 浅拷贝会有内存重复释放的问题
    // SmartPtr<int> p1(new int(2));
    // SmartPtr<int> p2(p1);
    // return 0;

    //auto_ptr永远让最后一个指针管理资源(会转移资源的所有权)，前面的指针全部置为nullptr
    //不推荐在容器里面使用auto_ptr,因为容器里面经常会发生拷贝
    auto_ptr<int> a1(new int(2));
    auto_ptr<int> a2(a1);
    *a2 = 20;
    //cout << *a1 << endl;


    // boost::scoped_ptr<int[]> ptr(new int[5]);
    // ptr[2] = 2;


    unique_ptr<int> up(new int);
    unique_ptr<int> up1(std::move(up));
    

    



    return 0;
}
