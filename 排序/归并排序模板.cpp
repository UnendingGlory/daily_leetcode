#include <iostream>
#include <vector>
using namespace std;

vector<int> A{1, 3, 7, 4, 6, 9, 2};

// 将两个有序数组归并 A[l...r]和A[s...e]，双指针法
void merge(int left, int right, int start, int end)
{
    vector<int> temp; // 辅助数组
    int i = left, j = start;
    while(i <= right && j <= end)
    {
        if(A[i] <= A[j]) temp.push_back(A[i++]);
        else temp.push_back(A[j++]);
    }
    // 复制剩余元素
    while(i <= right) temp.push_back(A[i++]);
    while(j <= end) temp.push_back(A[j++]);
    // 将temp复制回原数组
    for(int i = 0; i < temp.size(); ++i) A[left + i] = temp[i];
}

// 归并排序主体，递归，闭区间
void mergeSort(int left, int right)
{
    if(left < right)
    {
        int mid = left + ((right - left) >> 1);
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, mid + 1, right);
    }
}

int main()
{
    for(int i = 0; i < A.size(); ++i)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    mergeSort(0, A.size() - 1);
    for(int i = 0; i < A.size(); ++i)
    {
        printf("%d ", A[i]);
    }
    return 0;
}