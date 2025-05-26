

/*
如何解释多态

静态多态：编译时期的多态（函数重载  模板（函数模板 类模板））
动态多态：在继承结构中，基类指针指向派生类对象，通过该指针/引用调用同名的覆盖方法
基类指针 指向那个派生类对象就会调用哪个派生类的覆盖方法  称为多态
多态底层是通过动态绑定来实现的。基类指针指向谁，就会访问谁的vfptr，就会访问对应对象的vftable。
拿出来的当然是对应的派生类对象的方法。



继承的好处是什么：
1 可以做代码复用
2 在基类中给所有派生类提供统一的虚函数接口，让派生类进行重写，然后就可以使用多态。
3 更方便的添加新的类，而不需要改动现有的方法。
*/

#include <iostream>
#include <string>
using namespace std;

class Animal
{
public:
    Animal(string name) : m_name(name) {}
    virtual void bark() {}

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
void bark(Animal &a)
{
    a.bark();//bark是虚函数   动态绑定
}

int main()
{
    Cat cat1("猫");
    Dog dog1("狗");
    Pig pig1("猪");
    bark(cat1);
    bark(dog1);
    bark(pig1);
    return 0;
}