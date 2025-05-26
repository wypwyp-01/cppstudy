#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
构造函数和析构函数
- 名字和类名一样
- 没有返回值
*/

class SeqStack
{
public:
    SeqStack(int size = 10)//构造函数带参数，可以有多个（重载）
    {
        cout << this << "SeqStack()" << endl;
        m_pstack = new int[size];
        m_top = -1;
        m_size = size;
    }
    ~SeqStack()//不带参数，析构函数只能有一个
    //析构函数可以自己调用  但是不建议！！！
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
    SeqStack s;
    SeqStack s2;
    SeqStack * s3 = new SeqStack(2);
    //不加delete只有前两个调用了析构函数，堆上的对象一定要手动delete
    
    for (int i = 0; i < 15; i++)
    {
        s.push(i);
    }
    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
    cout << "empty:" << s.empty() << endl;
    delete s3;//加了delete三个对象都调用了析构函数
    return 0;
}