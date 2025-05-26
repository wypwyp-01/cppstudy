









#### 注意事项

1 当面试官提问问题后，不要着急作答，适当停一下，整理一下逻辑思路

2 对于简单问题的回答，尽量不要照本宣科，









### 基础课程

#### 04模板编程

##### 0401实现vector













### 高级课程

#### 03智能指针

裸指针  需要手动释放  否则可能造成内存泄漏

可能忘了手动释放，

或者写了手动释放的逻辑，但是由于程序的逻辑执行顺序和预想的不一样，导致手动释放资源的代码没有运行到



智能指针：能做到资源的自动释放

利用 栈上的对象出作用域自动析构的特征，来做到资源的自动释放



智能指针能否定义到堆上？不能





最简单的智能指针：

```c++
template <class T>
class SmartPtr
{
public:
    SmartPtr(T *ptr = nullptr) : m_ptr(ptr) {}
    ~SmartPtr()
    {
        cout << "~SmartPtr()" << endl;
        if (m_ptr)
            delete m_ptr;
    }

    T &operator*() { return *m_ptr; }

    T *operator->() { return m_ptr; }

private:
    T *m_ptr;
};
```

存在的问题：默认的浅拷贝会存在内存重复释放的问题



c++提供的四种智能指针：

**auto_ptr:**

auto_ptr永远让最后一个指针管理资源(会转移资源的所有权)，前面的指针全部置为nullptr

不推荐在容器里面使用auto_ptr,因为容器里面经常会发生拷贝

  











