




/*
‘函数参数传递过程中，对象优先按引用传递，不要用值传递
（少一个拷贝构造  一个析构）
函数返回对象的时候，尽量返回临时对象，而不要返回定义过的对象
（少一个拷贝构造  一个析构）
函数返回的是对象，接受返回值的时候，应该以初始化的方式，而不是赋值的方式接受
（少一个t2的默认构造，少一个临时对象的参数构造、析构、t2的赋值变为参数构造）

到最后只有四个函数
*/






