


/*

一  关键字和语法
auto：自动类型推导  根据右值，推导出右值的的类型，然后左边变量的类型也就已知了
nullptr：指针专用，能和整数进行区分。（NULL是一个宏定义，就是整数0  #define NULL 0）
for(Type val : container)     遍历数组、容器等。底层就是通过指针或者迭代器来实现的
右值引用 ：move移动语义函数和forward类型完美转发函数
模板的新特性：typename...A   表示可变参


二 函数对象和函数对象
function函数对象
bind绑定器（bind1st和bind2st + 二元函数对象 = 一元函数对象）
lambda表达式

三 智能指针
shared_ptr和weak_ptr

四  容器
unordered_set和unordered_map
array数组(array底层是数组)和forward_list前向链表

五 c++语言级别支持的多线程

*/