

#include <iostream>
using namespace std;
class Test
{
private:
    int m_a;

public:
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

int test1()
{
    Test t1;      // 带参构造
    Test t2(t1);  // 拷贝构造
    Test t3 = t1; // 拷贝构造

    // Test(20);//显示生成临时对象
    Test t4 = Test(20); // 调用带参构造  和Test t4(20)没有区别
    // c++编译器对于对象构造的优化  用临时对象生成新对象的时候，临时对象不产生，直接构造新对象

    t4 = Test(50); // 调用了带参构造和赋值运算符  除了语句，临时对象就会被析构
    t4 = t2;       // 调用赋值运算符

    t4 = (Test)50; // 把整数强制转换成 Test    也是调用带参构造和赋值运算符
    return 0;
}

int test2()
{

    // Test * p1 = &Test(1);//用指针指向临时对象是不安全的
    const Test &ref1 = Test(40);
    cout << "------" << endl;

    return 0;
}
class Test3
{
private:
    int m_a;
int m_b;
public:
    Test3(int a = 10,int b = 20) : m_a(a),m_b(b)
    {
        cout << "Test(int a = 10)" << endl;
    }
    ~Test3()
    {
        cout << "~Test()" << endl;
    }
    Test3(const Test3 &t) : m_a(t.m_a),m_b(t.m_b)
    {
        cout << "Test(const Test &t)" << endl;
    }
    Test3 &operator=(const Test3 &t)
    {
        m_a = t.m_a;
        m_b = t.m_b;
        cout << "operator=" << endl;
        return *this;
    }
};
Test3 t1(10,10);//1 带参构造
int main()
{

    Test3 t2(20,20);//3 带参构造
    Test3 t3 = t2;//4 拷贝构造
    static Test3 t4 = Test3(30,30);//5 第一次运行的时候构造  带参构造
    t2 = Test3(40,40);//6 带参构造  赋值运算符  析构
    t2 = (Test3)(50,50);//7 带参构造  赋值运算符  析构
    t2 = 66;//8 带参构造  赋值运算符  析构
    Test3 * p1 = new Test3(70,70);//9 带参构造
    Test3 * p2 = new Test3[2];//10 两个带参构造
    //Test3 * p3 = &Test3(80.80);
    const Test3 & ref1 = Test3(90,90);//11 带参构造
    delete p1;//12 析构
    delete[] p2;//13 两个析构

    return 0;
}
Test3 t5(100,100);//2 带参构造