#include <iostream>
#include <climits>
using namespace std;
class SeqStack;

/*
this指针 -》 类 -》很多对象使用一套成员方法
成员方法，方法的参数都会添加一个this指针

构造函数
        定义对象时，自动调用的，可以重载，构造完成，对象产生了
析构函数
        不带参数，不能重载，只有一个析构函数。析构完成，对象就不存在了。
*/

/*
对象的深拷贝  浅拷贝
*/

class SeqStack
{
public:
    SeqStack(int size = 10) // 构造函数带参数，可以有多个（重载）
    {
        cout << this << "SeqStack()" << endl;
        m_pstack = new int[size];
        m_top = -1;
        m_size = size;
    }
    SeqStack(const SeqStack &s)
    {
        // 自定义拷贝构造函数  因为浅拷贝现在有问题
        m_top = s.m_top;
        m_size = s.m_size;
        m_pstack = new int[s.m_size];
        for (int i = 0; i <= s.m_top; i++)
        {
            m_pstack[i] = s.m_pstack[i]; // 为什么用for循环，不用memcpy？就是为了防止浅拷贝
        }
    }
    void operator=(const SeqStack &s)
    {
        //防止自己给自己赋值
        if(this == &s){
            return ;
        }
        // 应该先把内存释放掉
        if (m_pstack)
        {
            delete[] m_pstack;
        }
        // 然后进行赋值
        m_top = s.m_top;
        m_size = s.m_size;
        m_pstack = new int[s.m_size];
        for (int i = 0; i <= s.m_top; i++)
        {
            m_pstack[i] = s.m_pstack[i]; // 为什么用for循环，不用memcpy？就是为了防止浅拷贝
        }
    }
    ~SeqStack() // 不带参数，析构函数只能有一个
    // 析构函数可以自己调用  但是不建议！！！
    {
        cout << this << "~SeqStack()" << endl;
        if (m_pstack)
        {
            delete[] m_pstack;
            m_pstack = nullptr;
        }
    }
    int top()
    {
        if (empty())
        {
            cout << "栈空" << endl;
            return INT_MIN;
        }
        return m_pstack[m_top];
    }
    void pop()
    {
        // 出栈
        if (empty())
        {
            cout << "栈空" << endl;
            return;
        }
        m_pstack[m_top] = 0;
        m_top--;
    }
    void push(int num)
    {
        // 入栈
        if (m_top < m_size - 1)
        {
            m_top++;
            m_pstack[m_top] = num;
        }
        else
        {
            int *temp = new int[2 * m_size];
            int i = 0;

            for (; i < m_size;)
            {
                temp[i] = m_pstack[i];
                ++i;
            }
            m_top = i;
            temp[m_top] = num;
            m_size = 2 * m_size;
            delete[] m_pstack;
            m_pstack = temp;
            temp = nullptr;
        }
    }
    bool empty()
    {
        return m_top == -1;
    }

private:
    int *m_pstack;
    int m_top; // top指向栈顶元素，初始化为-1
    int m_size;
};

int main()
{
    SeqStack s; // 没有提供任何构造函数的时候，会自动生成默认构造和默认析构函数
    // 默认构造和默认析构函数是空函数  什么也不做
    SeqStack s1(10);
    SeqStack s2 = s1; //  调用拷贝构造函数  拷贝构造函数 是内存的拷贝   浅拷贝  在析构的时候同一份资源就会释放两次
    // 对象如果占用外部资源  浅拷贝就会出现问题

    


    // 不仅发生了浅拷贝，s2指向的资源还丢了
    s2 = s1; // 这是赋值操作    调用的是默认的赋值函数  这个函数也是直接的内存拷贝

    return 0;
}
