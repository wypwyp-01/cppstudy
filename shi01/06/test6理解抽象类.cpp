/*
抽象类
抽象类和普通类有什么区别
拥有纯虚函数的类叫做抽象类！
抽象类不能再实例化对象，但是可以定义指针和引用变量

一般把什么类设计成抽象类
一般把基类设计成抽象类,把保留的接口设计成纯虚函数，不提供实现

*/

/*
定义animal的初衷  并不是让animal抽象某个实体的类型
string m_name    让所有的动物实体类通过继承animal直接复用该属性
给所有的派生类保留统一的覆盖/重写接口
*/

#include <iostream>
#include <string>
using namespace std;

class Animal
{
public:
    Animal(string name) : m_name(name) {}
    // 纯虚函数
    virtual void bark() = 0;

protected:
    string m_name;
};
// 以下是动物实体类
class Cat : public Animal
{
public:
    Cat(string name) : Animal(name) {}
    void bark() { cout << m_name << "bark miao miao miao" << endl; }
};
class Dog : public Animal
{
public:
    Dog(string name) : Animal(name) {}
    void bark() { cout << m_name << "bark wang wang wang" << endl; }
};
class Pig : public Animal
{
public:
    Pig(string name) : Animal(name) {}
    void bark() { cout << m_name << "bark heng heng heng" << endl; }
};

class Car
{
public:
    Car(string name,double oil) : m_name(name),m_oil(oil) {}
    double getLeftMils()
    {
        return m_oil * getMilsPerGallon();//动态绑定
    }
    string getName()const{
        return m_name;
    }

protected:
    virtual double getMilsPerGallon() = 0;
    string m_name;
    double m_oil;
};

class Bnze : public Car
{
public:
    Bnze(string name,double oil) : Car(name,oil) {}
    double getMilsPerGallon()
    {
        return 20.0;
    }
};

class Audi : public Car
{
public:
    Audi(string name,double oil) : Car(name,oil) {}
    double getMilsPerGallon()
    {
        return 22.0;
    }
};
class Bmw : public Car
{
public:
    Bmw(string name,double oil) : Car(name,oil) {}
    double getMilsPerGallon()
    {
        return 24.0;
    }
};
// 给外部提供一个统一的获取汽车剩余里程数的接口

double showCarLeftMiles(Car &c)
{
    cout << c.getName() << " left " << c.getLeftMils() << " miles" << endl;
    return c.getLeftMils();//静态绑定
}
int main()
{
    Bnze b("benchi",10);
    Audi a("aodi",10);
    Bmw bmw("baoma",10);
    showCarLeftMiles(b);
    showCarLeftMiles(a);
    showCarLeftMiles(bmw);
    return 0;
}