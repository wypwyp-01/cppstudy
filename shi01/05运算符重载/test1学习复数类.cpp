

#include <iostream>
using namespace std;

/*
c++的运算符重载：使对象的运算表现的和编译器内置类型一样

*/

class CComplex
{
public:
    friend istream & operator>>(istream & in,CComplex &c);
    friend CComplex operator+(const CComplex &a, const CComplex &c);
    // friend CComplex operator+(const CComplex &a, const CComplex &c);
    // friend CComplex operator+(int a, const CComplex &c);
    friend ostream &operator<<(ostream &out, const CComplex &c);
    CComplex(int x = 0, int y = 0) : m_real(x), m_image(y)
    {
    }

    // CComplex operator+(const CComplex &c) const
    // {
    //     return CComplex(c.m_real + this->m_real, c.m_image + this->m_image);
    // }

    void show()
    {
        cout << this->m_real << "+" << this->m_image << "i" << endl;
    }

    CComplex& operator++()
    { // 不带参数是前置++
        ++m_real;
        return *this;
    }

    CComplex operator++(int)
    { // 带int参数的是后置++
        CComplex temp = *this;
        ++m_real;
        return temp;
    }

    void operator+=(const CComplex &c)
    {
        *this = *this + c;
    }

private:
    int m_real;
    int m_image;
};
ostream &operator<<(ostream &out, const CComplex &c)
{
    out << c.m_real << "+" << c.m_image << "i";
    return out;
}

istream & operator>>(istream & in,CComplex &c){
    in >> c.m_real >> c.m_image ;
    return in;
}

CComplex operator+(const CComplex &a, const CComplex &c)
{
    return CComplex(a.m_real + c.m_real, c.m_image + a.m_image);
}

int main()
{

    CComplex c1(10, 1);
    CComplex c2(10, 1);
    CComplex c3 = c1 + c2 + c1; // 加法运算符的重载函数

    CComplex c4 = c1 + 20; // 编译器会把20转换成CComplex类
    c3.show();
    c4.show();
    cout << "c4:" << c4 << endl;
    // 编译器在对象运算的时候，会调用对象的运算符函数，优先调用成员方法，
    // 如果没有成员方法，就在全局作用域找合适的重载函数
    CComplex c5 = 80 + c1; // 这里调用的是20的加法运算符，但是int的加法运算符没有和CComplex相加的
    c5.show();

    CComplex c6 = c1++;
    c6.show();
    c1.show();

    CComplex c7 = ++c1;
    c7.show();
    c1.show();

    c7 += c1;
    c7.show();
    c1.show();

    cin >> c7 >> c1;
    cout << c7 << endl << c1 << endl;

    return 0;
}
