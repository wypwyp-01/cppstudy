#include <iostream>
using namespace std;
#include <ctime>
#include <vector>
/*
选择基准数建议从中间位置进行选择
时间
最好 平均 ：O(n logn)
最坏：O(n方)

空间
最好 平均 ：O(logn)
最坏：O(n)

不稳定


*/

int partition(int left, int right, vector<int> &nums)
{
    // int index = rand() % (right - left + 1) + left;
    int index = (left + right) / 2; // 取中间
    cout << index << " " << nums[index] << endl;
    int temp = nums[index];
    swap(nums[left], nums[index]);
    while (left < right)
    {
        while (left < right && nums[right] >= temp)
        {
            --right;
        }
        nums[left] = nums[right];
        while (left < right && nums[left] < temp)
        {
            ++left;
        }
        nums[right] = nums[left];
    }
    nums[left] = temp;
    return left;
}

void quicksort(int left, int right, vector<int> &nums)
{
    if (left < right)
    {
        int index = partition(left, right, nums);
        quicksort(left, index - 1, nums);
        quicksort(index + 1, right, nums);
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
    quicksort(0, data.size() - 1, data);
    cout << "排序之后的数据:    ";
    for (const auto &item : data)
    {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
