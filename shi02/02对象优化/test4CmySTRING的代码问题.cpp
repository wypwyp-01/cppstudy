
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
        cout  << "String()" << endl;
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

        cout  << "~String()" << endl;
        if (m_str)
        {
            delete[] m_str;
            m_str = nullptr;
        }
    }

    String(const String &str)
    {
        cout  << "String(const String &)" << endl;
        m_str = new char[strlen(str.m_str) + 1];
        strcpy(m_str, str.m_str);
        m_str[strlen(str.m_str)] = '\0';
    }

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

    const char *c_str() const{ return this->m_str; }

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


String GetString(const String & str){
    const char * pstr = str.c_str();
    String tempstr(pstr);//3 参数构造   5 析构
    return tempstr;
}
void test1()
{

    String str1("aaaaaa");//1 参数构造
    String str2 ;// 2 参数构造
    str2 = GetString(str1);//4 拷贝构造 tempstr拷贝构造临时对象 6 赋值运算符 7 析构临时对象
    cout << str2.c_str() << endl;
    //8 9 析构str1 2
    
}

int main()
{
    test1();

    return 0;
}
