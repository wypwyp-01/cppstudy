
/*
实现cpp   STL里面的顺序容器  vector
*/
// #include <vector>
#include <iostream>
using namespace std;

template <class T>
class vector
{
public:
    vector(int size = 10) // 空间的大小
    {
        _first = new T[size];
        _last = _first;
        _end = _first + size;
    }
    ~vector()
    {
        delete[] _first;
        _first = nullptr;
        _last = nullptr;
        _end = nullptr;
    }

    vector(const vector<T> &vec)
    {
        int size = vec._end - vec._first; // 空间大小
        _first = new T[size];
        // 只需要拷贝有效元素
        int len = vec._last - vec._first;
        for (int i = 0; i < len; ++i)
        {
            _first[i] = vec._first[i];
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
        delete[] _first;

        int size = vec._end - vec._first; // 空间大小
        _first = new T[size];
        // 只需要拷贝有效元素
        int len = vec._last - vec._first;
        for (int i = 0; i < len; ++i)
        {
            _first[i] = vec._first[i];
        }
        _last = _first + len;
        _end = _first + size;
        return *this;
    }

    void push_back(const T &val)
    { // 向容器末尾添加元素
        if (full())
        {
            expand();
        }
        *_last++ = val;
    }
    void pop_back()
    { // 从末尾删除元素
        if (empty())
        {
            return;
        }
        --_last;
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
        T *temp = new T[size * 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = _first[i];
        }
        delete[] _first;
        _first = temp;
        _last = _first + size;
        _end = _last + size;
        temp = nullptr;
    }

    T *_first; // 数组起始位置
    T *_last;  // 有效元素的后继位置
    T *_end;   // 数组空间的后继位置
};

int main()
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
