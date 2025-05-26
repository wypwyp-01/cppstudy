

#include <memory>
#include <iostream>
// #include<>
using namespace std;

/*
裸指针  需要手动释放  否则可能造成内存泄漏
可能忘了手动释放，
或者写了手动释放的逻辑，但是由于程序的逻辑执行顺序和预想的不一样，导致手动释放资源的代码没有运行到

智能指针：能做到资源的自动释放
利用 栈上的对象出作用域自动析构的特征，来做到资源的自动释放

智能指针能否定义到堆上？不能
*/
template <class T>
class RefCnt
{
public:
    RefCnt(T *ptr = nullptr) : mptr(ptr),mcount(0)
    {
        if (mptr)
            mcount = 1;
    }

    void addRef() { mcount++; }
    void delRef() { mcount--; }
    int getRef() { return mcount; }

private:
    T *mptr;
    int mcount;
};

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
        m_refcounter = new RefCnt<T>(m_ptr);
    }
    ~SmartPtr()
    {
        cout << "~SmartPtr()" << endl;
        if (m_refcounter)
        {
            m_refcounter->delRef();
            if (m_refcounter->getRef() == 0)
            {
                delete m_ptr;
                m_ptr = nullptr;
            }
        }
    }

    T &operator*()
    {
        return *m_ptr;
    }

    T *operator->()
    {
        return m_ptr;
    }

    SmartPtr(const SmartPtr<T> &src) : m_ptr(src.m_ptr), m_refcounter(src.m_refcounter)
    {
        if (m_ptr)
            m_refcounter->addRef(); // 引用计数加一
    }

    SmartPtr<T> &operator=(const SmartPtr<T> &src)
    {
        if (this == &src)
            return *this;
        // 释放或不释放原来资源
        m_refcounter->delRef();
        if (m_refcounter->getRef() == 0)
        {
            delete m_ptr;
        }
        m_ptr = src.m_ptr;
        m_refcounter = src.m_refcounter;
        m_refcounter->addRef();
        return *this;
    }

private:
    T *m_ptr;                // 指向资源的指针
    RefCnt<T> *m_refcounter; // 指向该资源引用计数对象的指针
};

int main()
{
    /*
    带引用计数的智能指针shared_ptr和weak_ptr
    带引用计数：多个智能指针可以管理同一个资源
    带引用计数：给每一个对象资源，匹配一个引用计数
    智能指针引用资源的时候，引用计数加一，出作用域不再使用资源的时候，引用计数减一。
    引用计数减一后不为零，说明还有别的智能指针使用资源
    引用计数减一后为零，说明没有智能指针使用资源，要析构资源。
    */
    SmartPtr<int> ptr1(new int(3));
    SmartPtr<int> ptr2(ptr1);
    SmartPtr<int> ptr3;
    ptr3 = ptr2;
    cout << *ptr2 << endl
         << *ptr3 << endl;
    return 0;
}
