

/*
哪些函数不能实现成虚函数
    1 虚函数需要依赖对象
    2 虚函数能产生地址存储在vftable中(对象存在-》vfptr-》vftable-》虚函数地址)

    构造函数：不能设计成虚函数（因为构造函数完成了才会产生对象，构造函数中调用任何函数都是静态绑定）
    派生类对象的构造过程：先调用的是基类的构造函数，才调用派生类的构造函数

    static静态成员方法：不能设计成虚函数。static也不是依赖对象的。





虚析构函数
    析构函数是可以成为虚函数的（调用的时候对象存在）
什么时候把基类的析构函数必须实现成虚函数
    基类的指针（引用）指向对上new出来的派生类对象,它调用析构函数的时候必须发生动态绑定，否则会导致派生类的析构函数无法调用
    

*/

#include <iostream>

using namespace std;

class Base
{
public:
    Base(int data) : m_a(data) {cout << "Base()" << endl;}
    virtual void show()
    {
        cout << "Base::show()" << endl;
        cout << m_a << endl;
    }
    virtual void show(int data)
    {
        cout << "Base::show(int data)" << endl;
        cout << m_a << endl;
    }
    virtual ~Base() { cout << "~Base()" << endl; }

protected:
    int m_a;
};

class Derive : public Base
{
public:
    Derive(int data = 20) : Base(data), m_b(data * 2) {cout << "Derive()" << endl;}
    int getb() { return m_b; }
    void show()
    {
        cout << "Derive::show()" << endl;
        cout << m_a << " " << m_b << endl;
    }
    void show(int data){cout << "Derive::show(int data)" << endl;cout << m_a << " " << m_b << endl;}
    ~Derive() { cout << "~Derive()" << endl; }

private:
    int m_b;
};
int main(){


    //Base类的析构函数没有被声明为虚函数。
    //因此，当通过Base类的指针pb删除Derive类的对象时，只会调用Base类的析构函数，而不会调用Derive类的析构函数。
    //Base类型  -》去看析构函数的类型-》不是虚函数-》静态绑定  只会调用基类的析构函数
    
    //基类的析构函数是virtual  派生类的析构函数自动成为虚函数
    //如果Base声明为虚函数，就会调用Derive的析构函数。
    Base * pb = new Derive(10);
    pb->show(111);
    delete pb;//没有调用派生类的析构函数



    //这里没有调用 delete pb;，d 是一个自动对象（栈对象），
    //作用域结束时会自动调用析构函数。这时候 C++ 会自动调用 Derive 和 Base 的析构函数，
    //析构是 按继承层次从派生类到基类依次调用，
    // Derive d(10);
    // Base * pb = &d;
    // pb->show();
}