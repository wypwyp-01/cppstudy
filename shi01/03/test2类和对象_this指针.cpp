#include <iostream>
#include <string>
#include <string.h>
using namespace std;
/*
类：实体的抽象类型
实体（属性 行为）： ->ADT（抽象数据类型）

OOP语言的四大特征是什么：抽象（通过访问限定符体现出来） 封装 继承 多态
*/
const int NAME_LEN = 20;
class CGoods
{
public:
    // 给外部提供共有的方法访问私有的属性
    // 左商品数据初始化用的
    void init(const char *name, double price, int amount);

    // 打印商品信息
    void showinfo();
    // 单独设置获取成员变量(给成员变量提供一组get set方法)
    void setName(char *name) { strcpy(m_name, name); }
    void setPrice(double price) { m_price = price; }
    void setAmount(int amount) { m_amount = amount; }
    // 类体内实现的成员方法，自动处理为inline
    const char *getName() { return m_name; }
    double getPrice() { return m_price; }
    int getAmount() { return m_amount; }

private: // 属性一般都是私有的
    char m_name[NAME_LEN];
    double m_price;
    int m_amount;
};

void CGoods::init(const char *name, double price, int amount)
{
    strcpy(m_name, name);
    m_price = price;
    m_amount = amount;
}

void CGoods::showinfo()
{
    cout << "name:" << m_name << endl;
    cout << "price:" << m_price << endl;
    cout << "amount:" << m_amount << endl;
}

int main()
{
    // CGoods可以定义无数的对象，每一个对象都有自己的成员变量，但是共享一套成员方法。
    // 对象的内存大小只和成员变量有关
    CGoods g1;
    // cout << g.m_price << endl;
    g1.init("面包", 10.0, 200);
    // init(&g1,"面包",10.0,200)
    g1.showinfo();
    g1.setPrice(20.0);
    g1.showinfo();
    g1.setAmount(100);
    g1.showinfo();

    CGoods g2;
    g2.init("空调", 10000, 50);
    g2.showinfo();
    cout << sizeof(CGoods);

    // this指针

    // show()怎么知道处理那个对象的信息？
    // init()怎么知道把信息初始化给哪一个对象
    // this指针
    // init(&g1,"面包",10.0,200)
    // 类的成员方法一经编译，所有的方法参数，都会加一个this指针，接受调用该方法的对象的地址
    return 0;
}
