#include <iostream>
using namespace std;
#include <ctime>
#include <vector>

/*
选择排序，选择的是位置，而不是值
升序排序，选最小值
降序排序，选最大值

最好最坏平均：O(n方)


不稳定
原因在于，当选择最小元素并进行交换时，可能会将相等元素的相对位置改变。
例如，数组 [5, 3, 5, 2] 经过第一次选择后变为 [2, 3, 5, 5]，两个 5 的相对顺序发生了改变。

*/

void searchsort(vector<int> &nums)
{
    int n = nums.size();
    int minindex = 0;
    for (int i = 0; i < n - 1; i++)
    {
        minindex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] < nums[minindex])
            {
                minindex = j;
            }
        }
        if (minindex != i)
        {
            swap(nums[i], nums[minindex]);
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
    searchsort(data);
    cout << "排序之后的数据:    ";
    for (const auto &item : data)
    {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
