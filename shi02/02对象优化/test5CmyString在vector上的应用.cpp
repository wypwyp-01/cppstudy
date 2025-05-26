

#include <iostream>
using namespace std;

#include <cstring>

class String
{
public:
    friend ostream &operator<<(ostream &out, const String &str);
    friend String operator+(const String &str1, const String &str2);
    String(const char *str = nullptr)
    {
        cout << "String()" << endl;
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

        cout << "~String()" << endl;
        if (m_str)
        {
            delete[] m_str;
            m_str = nullptr;
        }
    }

    // 带左值引用参数的拷贝构造
    String(const String &str)
    {
        cout << "String(const String &)" << endl;
        m_str = new char[strlen(str.m_str) + 1];
        strcpy(m_str, str.m_str);
        m_str[strlen(str.m_str)] = '\0';
    }

    // 带右值引用参数的拷贝构造
    String(String &&str) // str引用的就是一个临时对象
    {
        cout << "String(String &&)" << endl;
        m_str = str.m_str;
        str.m_str = nullptr;
    }

    // 带左值引用参数的赋值运算符
    String &operator=(const String &str)
    {
        cout << "operator=()" << endl;
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

    // 带右值引用参数的赋值运算符
    String &operator=(String &&str)
    {
        cout << "operator=(String &&str)" << endl;
        if (this == &str)
        {
            return *this;
        }
        if (m_str)
        {
            delete[] m_str;
        }

        m_str = str.m_str;
        str.m_str = nullptr;
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

    const char *c_str() const { return this->m_str; }

private:
    char *m_str;
};

ostream &operator<<(ostream &out, const String &str)
{
    out << str.m_str;
    return out;
}

String operator+(const String &str1, const String &str2)
{
    int len = strlen(str1.m_str) + strlen(str2.m_str);
    String tmp;
    tmp.m_str = new char[len + 1];
    strcpy(tmp.m_str, str1.m_str);
    strcat(tmp.m_str, str2.m_str);
    return tmp;
}

String GetString(const String &str)
{
    const char *pstr = str.c_str();
    String tempstr(pstr); // 3 参数构造   5 析构
    return tempstr;
}
#include <vector>

void test1()
{
    String str1 = "aaa";
    vector<String> vec;
    vec.reserve(2);

    cout << "---------------------" << endl;
    vec.push_back(str1);
    vec.push_back(String("bbb"));
    cout << "---------------------" << endl;
}
/*
String()
---------------------
String(const String &)/拷贝构造到vec[0]
String()//创建临时对象
String(String &&)//调用右值引用的拷贝构造拷贝到vec[1]
~String()
---------------------
~String()
~String()
~String()
*/
int main()
{
    test1();

    return 0;
}
