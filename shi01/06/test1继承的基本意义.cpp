/*

*/
#include <iostream>
using namespace std;
/*
继承的本质和原理：
继承的本质：a 代码复用  b

类和类之间的关系
组合：a part of  一部分的关系
继承：a kind of  一种的关系

继承方式    基类的访问限定  派生类的访问限定    外部的访问限定
public继承      
            public          public              可以访问
            protected       protected           不可以访问
            private         不可见               不可以访问
protected继承  基类成员的访问限定  在派生类里面是不可能超过继承方式的
            public          protected能访问     不可以访问
            protected       protected能访问     不可以访问
            private         不可见              不可以访问
private继承
            public          private能访问       不可以访问
            protected       private能访问       不可以访问
            private         不可见              不可以访问

总结：
            外部只能访问对象public成员
            在继承结构中，派生类从基类可以继承过来private成员  但是派生类无法直接访问
            protected和private区别？在基类中，想被派生类访问  不想被外部访问  那么在基类中把相关成员定义成protected
            如果派生类和外部都不打算访问  那么在基类中定义成private

默认的继承方式是什么？
如果是用class定义派生类   默认是private
如果用struct定义派生类    默认是public
*/
class A
{
private:
    int m_b;

public:
    int m_a;

protected:
    int m_c;//只有自己和友元可以访问私有成员
};

class B : public A // 继承    A：父类 基类  B：子类 派生类
{
private:
    int m_e;

public:
    int m_d;

protected:
    int m_f;
};

int main()
{
    B b;
    cout << sizeof b;
    return 0;
}