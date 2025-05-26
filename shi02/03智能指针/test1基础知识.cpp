

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
    SmartPtr(T *ptr = nullptr) : m_ptr(ptr)
    {
    }
    ~SmartPtr()
    {
        cout << "~SmartPtr()" << endl;
        if (m_ptr)
            delete m_ptr;
    }

    T &operator*()
    {
        return *m_ptr;
    }

    T *operator->()
    {
        return m_ptr;
    }

private:
    T *m_ptr;
};

int main()
{
    SmartPtr<int> ptr1(new int(5));
    cout << *ptr1 << endl;
    *ptr1 = 20;
    cout << *ptr1 << endl;

    SmartPtr<Test> ptr2(new Test());
    ptr2->test();

    return 0;
}
