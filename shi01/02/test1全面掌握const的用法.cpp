#include <iostream>

using namespace std;

/*
怎么理解const
const修饰的变量不能够再作为左值（初始化完成后值不能够被修改）



在c和cpp中const的区别是什么
c 中const可以不用初始化（c中叫常变量）  但是在cpp里面必须初始化，叫做常量
const的编译方式不同，c中按照一个变量来进行编译
c++中所有出现const常量名字的地方，都被常量的初始值替换了

但是int b = 1;
    const int a = b;叫常变量，就不存在替换了
*/

int main00()
{

    int a = 10;
    a = 20;

    const int b = 10;
    // b = 20;

    return 0;
}

int test()
{
    int b = 1;
    const int a = b; // c 中const可以不用初始化  但是在cpp里面必须初始化
    int *p = (int *)&a;
    //*p = 30;
    b = 20;
    // 因为a是直接读取值，而后面是直接读取内存，所以会不一样
    cout << a << endl
         << *p << endl
         << *(&a) << endl
         << b << endl; // 会输出1 30 30
    // 因为编译器做了优化会认为a永远是1，并可能直接把它的值嵌入到代码中（而不是读内存）。

    return 0;
}
int main(){
    int a = 1;
    const int b = a;
    a = 2;
    cout << b << endl;
    return 0;
}