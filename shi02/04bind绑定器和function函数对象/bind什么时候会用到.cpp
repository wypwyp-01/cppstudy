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
    bool operator()(const T & t)
    {
        return t < 70;
    }
};

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
    auto it1 = find_if(v.begin(), v.end(), bind1st(greater<int> (),70)); // 需要一个一元函数对象
    if(it1 != v.end()){
        v.insert(it1,70);
    }
    show(v);
    
}
