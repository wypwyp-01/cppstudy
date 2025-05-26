

/*
    虚函数和动态绑定 问题：是不是虚函数的调用一定是动态绑定？不是的
    在类的构造函数当中，调用虚函数，也是静态绑定。（构造函数中调用其他函数，不会发生动态绑定）
    静态绑定 用对象本身调用虚函数，是静态绑定
    动态绑定 （必须由指针(引用)调用虚函数  才会发生动态绑定）
    基类指针指向基类  /  派生类   以及派生类指针指向派生类   都会发生动态绑定
*/
#include <iostream>
using namespace std;
class Base
{

public:
    Base(int data = 20) : m_a(data) {}
    virtual void show() { cout << "Base::show()" << endl; }

protected:
    int m_a;
};

class Derive : public Base
{
public:
    Derive(int data = 20) : Base(data) {}
    void show() { cout << "Derive::show()" << endl; }

protected:
    int m_b;
};
int main()
{
    Base b;
    Derive d;

    //静态绑定 用对象本身调用虚函数，是静态绑定
    b.show();
    d.show();

    //动态绑定 （必须由指针调用虚函数  才会发生动态绑定）
    //基类指针指向基类  /  派生类   以及派生类指针指向派生类   都会发生动态绑定
    Base *pb1 = &b;
    pb1->show();
    Base *pb2 = &d;
    pb2->show();




    return 0;
}