#include <iostream>
#include<typeinfo>
using namespace std;
/*
总结一;
如果类里面定义了虚函数，那么编译阶段 编译器需要给这个类类型产生一个唯一的vftable,
虚函数表中主要存储的内容就是RTTI信息和虚函数的地址。
当程序运行时每一张虚函数表都会加载到内存的.rodata区（只读数据区）

总结二：
一个类里面定义了虚函数，那么这个类定义的对象，其运行时，内存中开始部分，多存储一个vfptr虚函数指针，指向相应类型的虚函数表vftable，
一个类型定义的多个对象，他们的vfptr指向的都是同一张虚函数表

总结三：
一个类的虚函数个数，不影响对象内存大小，影响的是虚函数表的大小

总结四
如果派生类中的方法和基类继承来的某个方法返回值 函数名  参数列表都相同 
而且基类的方法是虚函数，那么派生类的这个方法自动处理成虚函数

覆盖：基类的方法是虚函数，并且派生类对基类的虚函数进行了重写，派生类的方法自动处理成虚函数，称为覆盖

*/
class Base
{
public:
    Base(int data) : m_a(data) {}
    virtual void show() { cout << "Base::show()" << endl; cout << m_a << endl;}
    virtual void show(int data) { cout << "Base::show(int data)" << endl; cout << m_a << endl;}

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





int main(){
    Derive d(10);
    Base * pb = &d;
    pb->show();//如果发现show是普通函数，就进行静态的绑定（编译时期）
    //如果发现show是虚函数，就进行动态绑定。（因为只有运行时才知道调用的是那个函数，所以成为动态绑定）
    
    
    
    
    pb->show(222);//Base::show()如果是虚函数，就要进行动态绑定
    cout << sizeof(Base) << endl;//没有虚函数是4      有虚函数是8

    cout << sizeof(Derive) << endl;//没有虚函数是8     有虚函数是12


    /*
        pb的类型：Base   看有没有虚函数   
        如果没有虚函数，*pb识别的就是编译时期的类型
        如果Base有虚函数，*pb识别的就是运行时的类型

    */
    cout << typeid(pb).name() << endl;//Base *

    cout << typeid(*pb).name() << endl;//Base

    
    return 0;
}