
/*
实现cpp   STL里面的顺序容器  vector



/*
容器的空间配置器做四件事情：
1 把内存开辟   内存释放   对象构造  对象析构  分开处理

*/
// #include <vector>
#include <iostream>
#include <cstring>
using namespace std;

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

template <class T>
struct Allocator
{

    T *allocate(size_t size)
    {
        return (T *)malloc(size * sizeof(T));
    }
    void dealloacte(void *p)
    {
        free(p);
    }

    // void construct(T *p, const T &val)
    // {
    //     new (p) T(val); // 定位new
    // }

    // // 接受右值   一个右值引用变量本身还是一个左值
    // void construct(T *p, T &&val)
    // {
    //     new (p) T(std::move(val)); // 定位new
    // }
    template<class Ty>
    void construct(T *p, Ty &&val){
        //是左值，就匹配左值引用类型的构造
        //是右值   就匹配右值引用类型的构造
        new (p) T(std::forward<Ty>(val)); // 定位new
    }

    void destroy(T *p)
    {
        p->~T(); //~T()代表了T类型的析构函数
    }
};

// 容器底层内存开辟  内存释放  对象构造和析构   都通过空间配置器Allocator来实现
template <class T, class Alloc = Allocator<T>>
class vector
{
public:
    vector(int size = 10) // 空间的大小
    {
        // 需求：开辟空间和对象构造分开处理
        // 现在使用new，这两件事  一次性就做完了。
        // 如果传入的参数非常大，构造的时候，就要调用构造函数进行初始化，不合理

        //
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }
    ~vector()
    {
        // delete的时候会调用所有元素的析构函数
        // 应该是调用有效元素的 析构函数

        // delete[] _first;
        for (T *p = _first; p != _last; ++p)
        {
            _allocator.destroy(p); // 把有效元素进行析构操作
        }
        _allocator.dealloacte(_first); // 释放数组内存
        _first = nullptr;
        _last = nullptr;
        _end = nullptr;
    }

    vector(const vector<T> &vec)
    {
        int size = vec._end - vec._first; // 空间大小
        //_first = new T[size];
        _first = _allocator.allocate(size);
        // 只需要拷贝有效元素
        int len = vec._last - vec._first;
        for (int i = 0; i < len; ++i)
        {
            //_first[i] = vec._first[i];
            _allocator.construct(_first + i, vec._first[i]); // 在对应位置上构造
        }
        _last = _first + len;
        _end = _first + size;
    }

    vector<T> &operator=(const vector<T> &vec)
    {
        if (this == &vec)
        {
            return *this;
        }
        // delete[] _first;
        // 先把有效对象析构掉
        for (T *p = _first; p != _last; ++p)
        {
            _allocator(p);
        }
        // 在把内存释放掉
        _allocator.deallocate(_first);

        // int size = vec._end - vec._first; // 空间大小
        // // _first = new T[size];
        // // 只需要拷贝有效元素
        // int len = vec._last - vec._first;
        // for (int i = 0; i < len; ++i)
        // {
        //     _first[i] = vec._first[i];
        // }
        // _last = _first + len;
        // _end = _first + size;
        int size = vec._end - vec._first; // 空间大小
        //_first = new T[size];
        _first = _allocator.allocate(size);
        // 只需要拷贝有效元素
        int len = vec._last - vec._first;
        for (int i = 0; i < len; ++i)
        {
            //_first[i] = vec._first[i];
            _allocator.construct(_first + i, vec._first[i]); // 在对应位置上构造
        }
        _last = _first + len;
        _end = _first + size;
        return *this;
    }

    ////////////////////////////////////////////
    // 接受左值
    // void push_back(const T &val)
    // { // 向容器末尾添加元素
    //     if (full())
    //     {
    //         expand();
    //     }
    //     //*_last++ = val;
    //     // 在last指针指向的内存构造一个值为val的对象
    //     _allocator.construct(_last, val);
    //     ++_last;
    // }

    // // 带右值引用参数的
    // void push_back(T &&val)
    // { // 向容器末尾添加元素
    //     if (full())
    //     {
    //         expand();
    //     }

    //     _allocator.construct(_last, std::move(val));
    //     ++_last;
    // }

    //函数模板的类型推演 + 引用折叠
    //引用折叠   T && && val = T && val
    //           T & && val = T & val
    template <class Ty>
    void push_back(Ty &&val)
    {
        if (full())
        {
            expand();
        }

        //move 移动语义，不管是什么类型，都得到右值类型
        //forward类型的完美转发,能够识别左值和右值类型
        _allocator.construct(_last, std::forward<Ty>(val));
        ++_last;
    }
    //////////////////////////////////////////////////

    void pop_back()
    { // 从末尾删除元素
        // if (empty())
        // {
        //     return;
        // }
        // --_last;
        // 不仅要把指针--，还要析构删除的元素
        --_last;
        _allocator.destroy(_last);
    }

    // 返回容器末尾的元素值
    T back() const { return *(_last - 1); }
    bool full() const { return _last == _end; }
    bool empty() const { return _last == _first; }
    int size() const { return _last - _first; }

private:
    void expand() // 二倍扩容
    {
        int size = (_end - _first);
        // T *temp = new T[size * 2];
        T *temp = _allocator.allocate(2 * size);
        for (int i = 0; i < size; i++)
        {
            // temp[i] = _first[i];
            _allocator.construct(temp + i, _first[i]);
        }
        // delete[] _first;
        // 析构有效元素
        for (T *p = _first; p != _last; ++p)
        {
            _allocator.destroy(p);
        }
        // 释放空间
        _allocator.dealloacte(_first);

        _first = temp;
        _last = _first + size;
        _end = _last + size;
        temp = nullptr;
    }

    T *_first;        // 数组起始位置
    T *_last;         // 有效元素的后继位置
    T *_end;          // 数组空间的后继位置
    Alloc _allocator; // 定义容器的空间配置器对象
};

class Test
{

public:
    Test() { cout << "Test()" << endl; }
    ~Test() { cout << "~Test()" << endl; }

    void operator=(const Test &t) { cout << "operator=()" << endl; }
    Test(const Test &t) { cout << "Test(const)" << endl; }

private:
};

void test3()
{
    String str1 = "aaa";
    vector<String> vec;

    cout << "---------------------" << endl;
    vec.push_back(str1);
    vec.push_back(String("bbb"));
    cout << "---------------------" << endl;
}

int main()
{
    test3();
    return 0;
}

int test2()
{
    vector<Test> vec;
    cout << "-------------" << endl;
    Test t1, t2, t3;
    vec.push_back(t1);
    vec.push_back(t2);
    vec.push_back(t3);

    cout << "-------------" << endl;
    vec.pop_back(); // 应该调用对象的析构函数，但是不释放空间
    cout << "-------------" << endl;
    // vec.push_back(t3);
    cout << vec.size() << endl;
    return 0;
}
int test1()
{

    vector<int> vec;
    for (int i = 0; i < 20; i++)
    {
        vec.push_back(rand() % 100);
    }
    while (!vec.empty())
    {
        cout << vec.back() << endl;
        vec.pop_back();
    }
    cout << vec.size() << endl;
    return 0;
}
