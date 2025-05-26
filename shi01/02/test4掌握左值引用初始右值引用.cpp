


/*
c++ 的引用
引用和指针的区别？

1 左值引用和右值引用

2 引用的实例





引用是一种更安全的指针

指针是一个变量，他的值是另一个变量的地址。
引用跟原来的变量本质上是同一个东西，只是变量的别名。

1 汇编层面上
  定义指针变量和定义引用变量在汇编指令上是一样的，
  通过引用变量修改所引用内存的值，和通过指针变量修改所指向内存的值，其底层指令也是一样的
在使用上
2 引用必须初始化 指针可以不初始化。指针可以为空，可以改变指向。而引用不能为空并且在定义时必须初始化，初始化后不能改变。
3 引用只有一级引用，没有多级引用
4 sizeof指针得到的是指针的大小。sizeof引用得到的是所引用变量的大小。
5 引用的使用更加方便，改变指针指向内存，需要使用解引用，而引用可以直接更改，不需要使用解引用。




左值：有内存 有名字 值可以修改
右值：没有内存，没有名字，不能取地址
右值引用专门用来引用右值类型，指令上，自动产生临时量，然后 引用临时量。
右值引用本身是一个左值，有内存，有名字。
不能用右值引用变量来引用左值
*/
#include<iostream>
using namespace std;




int main(){

    int a  =10;
    int &b = a;

    int &&c = 30;
    c = 40;
    cout << c << endl;


    return 0;
}




int main1(){
    int a = 10;
    int * p = &a;

    int &b = a;

    *p = 20;
    cout << a << " " << *p << " " << b  << endl;
    b = 30;
    cout << a << " " << *p << " " << b  << endl;




    return 0;
}
int main2(){
    int arr[5] = {};
    int * p = arr;
    cout << sizeof(arr) << " " << sizeof p << endl;

    int (&q)[5] = arr;

    cout << sizeof(arr) << " " << sizeof q << endl;

    int cc = 10;
    int & dd = cc;
    cout << dd << endl;
    int ee = 20;
    dd = ee;
    cout << dd << endl;

    return 0;
}
int mian3(){

    return 0;
}