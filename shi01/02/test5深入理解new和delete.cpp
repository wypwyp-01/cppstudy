



#include<iostream>
using namespace std;



/*
malloc和free是c的库函数
new和delete是c++的运算符

new不仅可以做内存开辟 还可以做内存的初始化操作
malloc开辟内存是通过返回值和nullptr作比较，而new开辟内存失败通过抛出bad_alloc类型的异常来判断




new 有多少种？
int * p = new int(20);
int * p = new (nothrow) int(20);
const int * p = new const int(20);

//定位new
int data = 0;

int * p = new (&data) int(50)//在指定内存上划出制定大小的内存空间

*/

int main(){
    int * p = (int *)malloc(sizeof(int));
    *p = 20;
    free(p);//

    int * q = new int(20);
    delete q;

    int data = 0;

    int * p1 = new (&data) int(50);
    cout << data ;
    return 0;
}