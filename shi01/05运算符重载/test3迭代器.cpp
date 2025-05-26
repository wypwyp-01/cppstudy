
/*
迭代器的功能：提供统一的方式来透明的遍历容器
迭代器可以透明的访问容器内部的值
begin()和end()方法分别返回首元素迭代器，以及尾元素后继位置的迭代器

STL泛型算法接受的都是迭代器
泛型算法：- 全局的函数，给所有容器使用
泛型算法，需要有一套方式，能够统一的遍历所有的容器的元素

*/
#include <iostream>
using namespace std;

#include <cstring>

class String
{
public:
    friend ostream &operator<<(ostream &out, const String &str);
    friend String operator+(const String &str1, const String &str2);

    class iterator
    { // 给String字符串类型提供迭代器实现

    public:
        iterator(char *p = nullptr) : m_p(p) {};

        bool operator!=(const iterator &it) { return m_p != it.m_p; }

        void operator++()
        {
            ++m_p;
        }

        char &operator*() { return *m_p; }

    private:
        char *m_p;
    };

    iterator begin() // 返回首元素的迭代器表示
    {
        return iterator(m_str);
    }
    iterator end() // 返回容器末尾元素后继位置的迭代器表示
    {
        return iterator(m_str + size());
    }

    String(const char *str = nullptr)
    {
        if (str != nullptr)
        {
            m_str = new char[strlen(str) + 1];
            strcpy(m_str, str);
            m_str[strlen(str)] = '\0';
        }
        else
        {
            m_str = new char[1];
            m_str[0] = '\0';
        }
    }

    ~String()
    {
        if (m_str)
        {
            delete[] m_str;
            m_str = nullptr;
        }
    }

    String(const String &str)
    {
        m_str = new char[strlen(str.m_str) + 1];
        strcpy(m_str, str.m_str);
        m_str[strlen(str.m_str)] = '\0';
    }

    String &operator=(const String &str)
    {
        if (this == &str)
        {
            return *this;
        }
        if (m_str)
        {
            delete[] m_str;
        }

        m_str = new char[strlen(str.m_str) + 1];
        strcpy(m_str, str.m_str);
        m_str[strlen(str.m_str)] = '\0';

        return *this;
    }

    bool operator>(const String &str) const
    {
        return strcmp(this->m_str, str.m_str) > 0;
    }

    bool operator<(const String &str) const
    {
        return strcmp(this->m_str, str.m_str) < 0;
    }

    bool operator==(const String &str) const
    {
        return strcmp(this->m_str, str.m_str) == 0;
    }

    int size() const
    {
        return strlen(this->m_str);
    }

    char &operator[](int index)
    {
        if (index < strlen(this->m_str))
        {
            return m_str[index];
        }
    }

    const char *c_str() { return this->m_str; }

private:
    char *m_str;
};

ostream &operator<<(ostream &out, const String &str)
{
    out << str.m_str;
    return out;
}

// String operator+(const String &str1, const String &str2)
// {
//     int len = strlen(str1.m_str) + strlen(str2.m_str);
//     char *temp = new char[len + 1];
//     strcpy(temp, str1.m_str);
//     strcat(temp, str2.m_str);
//     //存在的问题：如果不构造临时对象tempstr会造成内存泄漏，
//     //但是构造了临时对象，又会有拷贝次数过多的问题
//     String tempstr(temp);
//     delete[] temp;
//     temp[len] = '\0';
//     return temp;
// }
String operator+(const String &str1, const String &str2)
{
    int len = strlen(str1.m_str) + strlen(str2.m_str);
    String tmp;
    tmp.m_str = new char[len + 1];
    strcpy(tmp.m_str, str1.m_str);
    strcat(tmp.m_str, str2.m_str);
    return tmp;
}
void test1()
{
    String str1 = "hello world!";
    for (String::iterator it = str1.begin(); it != str1.end(); ++it)
    {
        cout << *it;
    }
    cout << endl;

    //使用for each遍历容器  底层还是使用begin() 和end()遍历的
    for (char c : str1)//去掉begin()和end()会报错此基于范围的“for”语句需要适合的 "begin" 函数，但未找到
    {
        cout << c << endl;
    }
}

int main()
{
    test1();

    return 0;
}
