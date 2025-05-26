

/*
c++语言级别提供的四种类型转换方式
const_cast  去掉常量属性的类型转换

static_cast 能够提供编译器认为安全的类型转换(没有任何联系的类型之间的转换会被否定)c不管有没有联系 会直接转换

reinterpret_cast    类似于c风格的强制类型转换（谈不上什么安全）

dynamic_cast    主要用在继承结构中可以支持RTTI类型识别的转换
*/

#include <iostream>
using namespace std;

class Base
{
public:
    virtual void func() = 0;
};

class Derive1 : public Base
{
public:
    void func() { cout << "Derive1" << endl; }
};

class Derive2 : public Base
{
public:
    void func() { cout << "Derive2" << endl; }
    // Derive2实现新功能的api接口函数
    // 指向其他的类型调用func
    // 指向Derive2调用下面的函数
    void derive2func()
    {
        cout << "Derive2func" << endl;
    }
};

void show(Base *p)
{
    Derive2 *pd2 = dynamic_cast<Derive2 *>(p);
    // 如果是转换类型成功，返回对象地址。转换不成功  返回nullptr
    if (pd2 != nullptr)
    {
        pd2->derive2func();
    }
    else
    {
        p->func();
    }
}

int main()
{

    Base * b1 = new Derive1;
    Base * b2 = new Derive2;
    cout << typeid(*b1).name() << endl << typeid(*b2).name() << endl ;
    Derive1 d1;
    Derive2 d2;
    show(&d1);
    show(&d2);

#if 0
    const int a = 10;
    //double *p2 = (double *)&a;//不报错
    int *p1 = const_cast<int*> (&a);//去掉const属性
    //double *p1 = const_cast<double*> (&a);//去掉const属性//报错
    //int b = const_cast<int> a;//报错 const_cast 中的类型必须是指针、引用或指向对象类型成员的指针C

    //大部分场景都是在使用static_cast
    int p = 1;
    //double * dp = static_cast<double *> (p);//报错
    double dp = static_cast<double> (p);
    int b = 10;
    char cb = static_cast<char> (b);


    double * dp = reinterpret_cast<double *> (p);//不会报错，但是不安全

#endif

    return 0;
}
