#include <iostream>
using namespace std;
#include <ctime>
#include <vector>

/*
稳定

时间：最好 最坏  平均   O(n log2n)
空间：最好 最坏  平均   O(n)用到了辅助数组B
*/



void merge(vector<int> &A, vector<int> &B, int low, int mid, int high)
{

    for (int i = low; i <= high; i++)
    {
        B[i] = A[i];
    }
    int i, j, k;
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high;)
    {
        if (B[i] <= B[j])
        {
            A[k++] = B[i++];
        }
        else
        {
            A[k++] = B[j++];
        }
    }
    while(i <= mid){
        A[k++] = B[i++];
    }
    while(j <= high){
        A[k++] = B[j++];
    }

}

void mergesort(vector<int> &A, vector<int> &B, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(A, B, low, mid);
        mergesort(A, B, mid + 1, high);
        merge(A, B, low, mid, high);
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
    vector<int> temp(data.size());
    mergesort(data, temp, 0, data.size() - 1);
    cout << "排序之后的数据:    ";
    for (const auto &item : data)
    {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
