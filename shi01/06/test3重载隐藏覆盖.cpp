#include <iostream>
using namespace std;



/*
1 重载关系
    一组函数要重载，必须在同意作用域中，而且函数名字相同，参数列表不同

2 隐藏（作用域的隐藏）关系
    在继承结构当中 派生类的同名成员把基类的同名成员隐藏掉了。

====================================================================
基类对象到派生类对象的转换
从下到上的转换  没有问题
发生对象切片现象。派生类对象被赋值给基类对象时，派生类对象的派生部分会被“切掉”，只保留基类部分

派生类对象到基类对象的转换
从上到下的转换  不可以

基类指针（引用）指向派生类对象
可以 只能访问基类部分的成员

派生类指针（引用）指向基类对象
不可以

在继承结构中  进行上下的类型转换  默认只支持从下到上的转换


*/





class Base
{
public:
    Base(int data) : m_a(data) {}
    void show() { cout << "Base::show()" << endl; cout << m_a << endl;}
    void show(int data) { cout << "Base::show(int data)" << endl; cout << m_a << endl;}

protected:
    int m_a;
};

class Derive : public Base
{
public:
    Derive(int data = 20) : Base(data), m_b(data * 2) {}
    int getb(){return m_b;}
    void show(){cout << "Derive::show()" << endl;cout << m_a << " " << m_b << endl;}
    //void show(int data){cout << "Derive::show(int data)" << endl;cout << m_a << " " << m_b << endl;}
private:
    int m_b;
};
int main()
{


    Base b(10);//基类对象
    Derive d(20);//派生类对象
    //b = d;//相当于从下到上的转换   没有问题
    //d = b;//报错
    Base * pb = &d;//基类指针指向派生类对象   只能访问基类部分的成员
    pb->show(111);
    //Derive * pd = &b;//报错








    #if 0
    Base b(2);
    b.show();
    b.show(445);//调用的肯定是基类的

    Derive d;
    d.show();
    d.show(10);//如果派生类没有定义show  调用基类的
    //如果派生类定义了一个show，那么就会把基类的所有的show都隐藏掉。（但是还可以通过作用域调用）
    //优先找派生类自己作用域的show成员，没有的话才会去基类里面找
    return 0;
    #endif
}