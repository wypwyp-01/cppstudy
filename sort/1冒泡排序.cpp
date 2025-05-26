
#include <iostream>
using namespace std;
#include <ctime>
#include <vector>

/*
冒泡排序：
n表示数组长度
外层循环：循环次数
n个元素遍历n - 1次

内层循环。遍历到第几个元素
比较的是遍历到的元素和后一个元素的值
第0次循环遍历到倒数第二个元素，所以是 < n - 1



最坏：O(n方)
平均：O(n方)
最好：O(n)
稳定：当两个元素相等时，不会交换位置
*/

void bubbleSort(vector<int> &nums)
{
    int n = nums.size();
    bool swapped = false;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                swapped = true;
                swap(nums[j], nums[j + 1]);
            }
        }
        if (swapped == false)
        {
            // 说明数据已经有序了，就没有必要再继续了
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    vector<int> data;
    cout << "排序前的原始数据:  ";
    for (int i = 0; i < 10; ++i)
    {
        data.push_back(rand() % 100);
        cout << data.back() << " ";
    }
    cout << endl;
    bubbleSort(data);
    cout << "排序之后的数据:    ";
    for (const auto &item : data)
    {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
