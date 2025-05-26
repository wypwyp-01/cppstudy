#include <iostream>
using namespace std;

class Test
{
private:
    int m_a;

public:
    int getData() const
    {
        return m_a;
    }
    Test(int a = 10) : m_a(a)
    {
        cout << "Test(int a = 10)" << endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }
    Test(const Test &t) : m_a(t.m_a)
    {
        cout << "Test(const Test &t)" << endl;
    }
    Test &operator=(const Test &t)
    {
        m_a = t.m_a;
        cout << "operator=" << endl;
        return *this;
    }
};


Test GetObject(Test t){

    int val = t.getData();
    Test tmp(val);//4 带参构造   6 析构tmp   7 析构t
    return tmp; //不能返回局部的或者临时对象的地址或引用
}





int main()
{
    Test t1;//1 带参构造
    Test t2 ;//2 默认构造
    t2 = GetObject(t1);//3 拷贝构造(t1拷贝构造t)  5 拷贝构造（tmp拷贝构造临时对象）
    //8 赋值运算符   临时对象赋给t2
    //9 临时对象析构
    //t2    t1析构
    return 0;
}
