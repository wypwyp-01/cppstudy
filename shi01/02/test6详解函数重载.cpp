

/*








什么是函数重载
1 一组函数，其中函数名相同，参数列表的个数或者类型不同，那么这一组函数就称作函数重载
2 一组函数称得上重载，一定是在同一个作用域当中的。
3 参数类型前面加const或者volatile的时候，是怎么影响形参类型的。
4 一组函数，函数名相同，参数列表也相同，仅仅是返回值不同，不是重载



c++为什么支持函数重载  c语言为什么不支持
c++代码在产生函数符号的时候，是由函数名+参数列表类型组成的，
c代码产生函数符号的时候，只由函数名决定


函数重载需要注意什么



c++和c代码怎么互相调用
只要是c++编译器，都内置了_cplusplus这个宏名
只有c++编译器才能识别extern"C"，所以extern"C"都是用在c++文件里面
c调用c++
把c++源码括在extern"C"里面

c++调用c代码
把c函数的声明括噪extern"C"里面

*/
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif
    int sum()
    {
        return 7;
    }
#ifdef __cplusplus
}
#endif

// void func(int a){

// }
// void func(const int a){

// }
int main1()
{

    int a = 10;
    const int b = 20;
    cout << typeid(a).name() << endl
         << typeid(b).name();

    return 0;
}

int main()
{
    cout << __FILE__ << endl;

    cout << __LINE__;
    return 0;
}
