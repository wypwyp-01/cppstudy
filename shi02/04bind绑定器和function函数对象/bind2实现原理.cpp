/*
c++11从boost库中引入了bind绑定器和function函数对象
*/
#include <iostream>
using namespace std;
#include <functional>
#include <vector>
#include <algorithm>
#include <ctime>

template <class Container>
void show(Container &con)
{
    for (auto it : con)
    {
        cout << it << " ";
    }
    cout << endl;
}
template <class T>
class com
{
    bool operator()(const T &t)
    {
        return t < 70;
    }
};

template <class It, class Compare>
It my_find_if(It first, It last, Compare comp)
{
    for (; first != last; ++first)
    {
        if (comp(*first))
        {
            return first;
        }
    }
    return last;
}

// 实现一元函数对象
template <class comp, class T>
class _mybind1st
{
public:
    _mybind1st(comp c, T val) : _comp(c), _val(val) //_mybind1st接受二元函数对象和要绑定的值，返回一元函数对象
    {
    }
    bool operator()(const T &sec)
    {                            // 接受外面传进来的第二个值
        return _comp(_val, sec); //_comp是二元函数对象，第一个参数是绑定的值，第二个参数是外面传进来的
        //_comp()是实际在代码中使用的，有两个参数，第一个是要绑定的，第二个是代码中传进来的
    }

private:
    comp _comp;
    T _val;
};

template <class Compare, class T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T &t)
{ // 参数：二元函数对象，要绑定的值值  返回值：一元函数对象
    return _mybind1st<Compare, T>(comp, t);
}

int main()
{
    srand(time(nullptr));
    vector<int> v(20);
    for (int i = 0; i < 20; ++i)
    {
        v[i] = rand() % 100 + 1;
    }
    show(v);
    // greater二元函数对象
    sort(v.begin(), v.end(), greater<int>()); // 降序排序
    show(v);
    // 把70按顺序插入到v中，   找到第一个小于70的数字
    /*
    绑定器的作用：绑定器+ 一元函数对象= 二元函数对象
    */
    auto it1 = my_find_if(v.begin(), v.end(), mybind1st(greater<int>(), 70)); // 需要一个一元函数对象
    if (it1 != v.end())
    {
        v.insert(it1, 70);
    }
    show(v);
}
