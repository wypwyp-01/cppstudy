#include <iostream>
using namespace std;
// 指向类成员（成员变量和成员方法）的指针

class Test
{

public:
    void func() { cout << "call Test::func" << endl; }
    static void static_func() { cout << "Test::static_func" << endl; }
    int ma;
    static int mb ;
};
int Test::mb = 30;//类外初始化
int main()
{
    //不能脱离对象访问类的成员变量
    //int *p = &Test::ma;//cannot convert ‘int Test::*’ to ‘int*’ in initialization
    Test t1;
    Test * t2 = new Test();

    //指向成员方法的指针
    //void (*funcp)() = &Test::func;
    void (Test::*funcp)() = &Test::func;
    (t1.*funcp)();
    void (*funcp2)() = &Test::static_func;//静态成员函数可以通过普通的函数指针访问
    (*funcp2)();




    #if 0
    int Test::*p = &Test::ma;
    t1.*p = 20;
    cout << t1.ma << endl;
    cout << t1.*p << endl;

    int * p2 = &Test::mb;//静态成员变量可以脱离对象访问
    cout << *p2 << endl;
    delete t2;
    #endif
    return 0;
}
