#include <iostream>
#include <string.h>
using namespace std;

/*
    日期类
*/
/*
构造函数的初始化列表  可以指定当前对象成员变量的初始化方式  尤其对于成员对象而言
*/
class CDate
{
private:
    int m_year;
    int m_month;
    int m_date;

public:
    CDate() { cout << "默认构造" << endl; }
    CDate(int y, int m, int d)
    {
        m_year = y;
        m_date = d;
        m_month = m;
        cout << "参数构造" << endl;
    }
    CDate(const CDate &d)
    {
        cout << "拷贝构造" << endl;
    }
    void show()
    {
        cout << m_year << ":" << m_month << ":" << m_date << endl;
    }
};

const int NAME_LEN = 20;
class CGoods
{
public:
    // 给外部提供共有的方法访问私有的属性
    // 左商品数据初始化用的

    CGoods(const char *name, double price, int amount, int y, int m, int d)
        : m_date(y, m, d), m_amount(amount), m_price(price) // 1 # 先执行构造函数的初始化列表
    {
        // 2 # 后执行构造函数函数体
        strcpy(m_name, name);
        // 在初始化列表初始化和函数体里面初始化有什么区别？
        // int amount = a; 和    初始化列表
        // int amount;amount = a;的区别    函数体
        // 对于内置类型没什么区别
        // 但是对于自定义类型    初始化列表可以指定使用的构造函数
        // 如果在函数体里面进行构造的话会先调用默认构造  再调用函数体里面执行的构造
        // m_date = CDate(y,m,d);//这样写会调用默认构造  参数构造
        // 初始化列表只会调用参数构造
    }

    // void init(const char *name, double price, int amount);

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
    CDate m_date; // 成员对象  1 分配内存  2 构造函数
};

void CGoods::showinfo()
{
    cout << "name:" << m_name << endl;
    cout << "price:" << m_price << endl;
    cout << "amount:" << m_amount << endl;
    m_date.show();
}
/*
构造函数的初始化列表
*/

int test1()
{
    CGoods g("面包", 2, 100, 2025, 4, 4);
    g.showinfo();
    return 0;
}

class Test
{
public:
    Test(int d = 10) : m_b(d), m_a(m_b)
    {
    }
    void show()
    {
        cout << m_a << " " << m_b << endl;
    }

private:
    int m_b;
    int m_a;
};
int main()
{
    Test t;
    t.show(); //初始化顺序是按照在类中定义的顺序进行的  所以如果m_a在mb前定义ma会输出随机值
    //如果m_a在mb后定义ma会输出10
    //成员变量的初始化和定义的顺序有关  和构造函数初始化列表中出现的顺序无关
    return 0;
}