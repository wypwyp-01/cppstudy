
#include <iostream>
using namespace std;

/*
派生类怎么初始化从基类继承而来的成员变量？
    1 派生类从基类可以继承来所有的成员，除构造函数和析构函数
    2 通过调用基类相应的构造函数来初始化
    3 派生类的构造函数和析构函数负责初始化和清理派生类部分，
    派生类从基类继承而来的成员的初始化和清理由基类的构造函数和析构函数负责



派生类对象构造和析构的过程：
    1 调用基类构造函数
    2 调用派生类自己的构造函数

    3 出作用域 调用派生类析构函数  释放派生类的外部资源
    4 调用基类的析构函数 释放派生类内存中从基类继承来的资源
*/

class Base
{
public:
    Base(int data) : m_a(data) { cout << "Base() " << endl; };
    ~Base() { cout << "~Base()" << endl; }

protected:
    int m_a;
};
class Derive : public Base
{

public:
    Derive(int data) : m_b(data), Base(data) { cout << "Derive()" << endl; }
    ~Derive() { cout << "~Derive()" << endl; }

private:
    int m_b;
};
int main()
{
    Derive d(2);
    /*
    Base()
    Derive()
    ~Derive()
    ~Base()
    构造和析构的顺序是相反的
    */
    return 0;
}