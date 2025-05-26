#include <iostream>
using namespace std;

/*


const修饰的量常出现的错误
1 常量不能再作为左值-》直接x修改常量的值
2 不能把常量的地址泄露给普通的指针或普通的引用-》间接修改常量的值


const和一级指针的结合

const此时的是离他最近的类型
这两种const修饰的表达式是 *p,所以*p不能再赋值了   指针指向的东西不能再赋值了。指针本身还能再赋值，还能再指向别的地方。
const int *p;
int const *p;

const修饰的是p指针本身，所以p本身不能修改，不能再指向其他的内存。   可以通过指针解引用修改指向的内存的值。
int * const p;

const int * const p;

总结：const和指针的类型转换公式：
int *   <- const int *是错误的
const int * 《- int *是可以的
int **    <=   const int **是错误的
const int **   <= int **  也是错误的
const和多级指针的结合  两边要么都有  要么都没有才能转换  否则都不能转换

int * const * q;//这是const和一级指针结合的情况
int * const * q  <-  int **正确
int **  <-   int * const * q  错误





const右边如果没有*的话，const是不参与类型的。
int * p = nullptr;
int * const p2 = nullptr;
这俩都是int *  相互转换没有问题

*/



/*
const 和二级指针的结合

const int **q;

int * const * q;

int ** const q;



*/
int test()
{
    const int a = 10;
    // int * p = &a;//"const int *" 类型的值不能用于初始化 "int *" 类型的实体
    const int *p = &a;

    return 0;
}
int test1()
{
    int *p = nullptr;
    int *const p2 = nullptr;
    cout << typeid(p).name() << endl;  // int *
    cout << typeid(p2).name() << endl; // int *
    return 0;
}
int main(){
    //int a = 10;
    //int * p = &a;
    //const int **q = &p;//const int **   <= int **
    /*
    
    */



    return 0;
}