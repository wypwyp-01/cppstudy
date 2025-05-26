
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
    String str1;
    String str2 = "aaa";
    String str3 = "bbb";
    String str4 = str2 + str3;
    String str5 = str2 + "ccc";

    String str6 = "ddd" + str2;
    cout << "str6:" << str6 << endl;

    if (str5 > str6)
    {
        cout << "str5 > str6" << endl;
    }
    else
    {
        cout << "str5 < str6" << endl;
    }

    int len = str6.size();

    for (int i = 0; i < len ; i++)
    {
        cout << str6[i] << endl;
    }
}

int main()
{
    test1();

    return 0;
}
