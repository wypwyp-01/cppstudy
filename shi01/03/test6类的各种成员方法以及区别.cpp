#include <iostream>
#include <string.h>
using namespace std;

/*
普通的成员方法：
    1 属于类的作用域
    2 调用该方法时需要依赖一个对象
    3 可以任意访问对象的私有成员变量
静态成员方法：
    1 属于类的作用域
    2 用类名：作用域调用
    3 可以任意访问对象的私有成员(仅限于不依赖于对象的成员（只能调用其他的static静态成员）)
    4 核心区别：普通方法会添加this形参变量，静态方法不会添加
const常成员方法：
    1 属于类的作用域
    2 调用依赖于一个对象 ，普通对象或者常对象都可以
    3 可以任意方法对象的私有成员  只能读不能写

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
    void show() const
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
        ++m_count; // 记录所有产生的新对象的数量
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
    void showinfo() const;
    // 单独设置获取成员变量(给成员变量提供一组get set方法)
    void setName(char *name) { strcpy(m_name, name); }
    void setPrice(double price) { m_price = price; }
    void setAmount(int amount) { m_amount = amount; }
    // 类体内实现的成员方法，自动处理为inline
    const char *getName() { return m_name; }
    double getPrice() { return m_price; }
    int getAmount() { return m_amount; }
    // 静态成员方法只能访问不依赖于对象的成员变量
    static int getcount() { return m_count; } // 静态成员方法  没有this指针  不需要依赖于对象调用
private:                                      // 属性一般都是私有的
    char m_name[NAME_LEN];
    double m_price;
    int m_amount;
    CDate m_date; // 成员对象  1 分配内存  2 构造函数
    static int m_count;
};
int CGoods::m_count = 0; // 静态成员变量不属于对象而是属于类

void CGoods::showinfo()
{
    cout << "name:" << m_name << endl;
    cout << "price:" << m_price << endl;
    cout << "amount:" << m_amount << endl;
    m_date.show();
}
//常方法：只要是只读的方法，一律实现成常成员方法
void CGoods::showinfo() const
{
    cout << "name:" << m_name << endl;
    cout << "price:" << m_price << endl;
    cout << "amount:" << m_amount << endl;
    m_date.show();
}

int main()
{
    CGoods g1("面包", 2, 100, 2025, 4, 4);
    g1.showinfo();

    CGoods g2("商品1", 2, 100, 2025, 4, 4);
    g2.showinfo();

    CGoods g3("商品2", 2, 100, 2025, 4, 4);
    g3.showinfo();

    CGoods g4("面包2", 2, 100, 2025, 4, 4);
    g4.showinfo();
    // 统计所有商品的总数量
    cout << "总数量:" << CGoods::getcount() << endl;
    const CGoods g5("非卖品", 100, 2, 2025, 4, 5); // 常对象
    g5.showinfo();//常对象不能调用普通方法  常量生成的是常量指针  而普通方法需要的是普通指针
    return 0;
}