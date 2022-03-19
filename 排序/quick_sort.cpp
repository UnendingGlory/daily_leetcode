/***************************************************************************
 *  @file       radix_sort.cpp
 *  @author     Wilosn.Wang
 *  @date       26  Nov 2020
 *  @remark     This code is a template for quick sort.
				quick sort实现方法就不赘述。主要讲下同为O(nlogn)的时间复杂度为什么
                往往快排比堆排序要快。最重要的一点就是quick sort是顺序访问，对cache
                友好，而堆结构要频繁跳跃访问，所以cache可能要频繁替换，会降低速度。
 *  @note
 ***************************************************************************/

#include "../header.h"
using namespace std;

class Solution {
public:
    // 返回在数组中的下标，双指针法
    int Patition(int left, int right, vector<int>& nums)
    {
        int temp = nums[left]; // 选取第一个元素作为枢轴
        while(left < right) // 未相遇
        {
            // 找到第一个比枢轴小的元素
            while(left < right && nums[right] >= temp) --right;
            swap(nums[left], nums[right]); // 小于，则交换
            // 这第二个while的等号一定要写，否则会造成死循环
            while(left < right && nums[left] <= temp) ++left;
            swap(nums[left], nums[right]);
        }
        return left;
    }

    // 快排，递归
    void quicksort(vector<int>&nums, int left, int right)
    {
        if(left >= right) return;
        int pos = Patition(left, right, nums);
        quicksort(nums, left, pos - 1); // 左边
        quicksort(nums, pos + 1, right); // 右边
    }

    // 递归
    vector<int> sortArray(vector<int>& nums) {
        quicksort(nums, 0, nums.size() - 1);
        return nums;
    }
};

// 简洁手撸版
void quickSort(int *arr, int l, int r)
{
    if(l >= r) return;
    // 下面进行patition操作
    int x = l, y = r, temp = arr[l]; // 最左侧作为枢轴元素，暂存
    while(x < y)
    {
        // 先找右边找比枢轴小的，注意x<y的判断
        while(x < y && arr[y] >= temp) --y;
        // 找到了则交换
        if(x < y) arr[x] = arr[y];
        while(x < y && arr[x] <= temp) ++x;
        if(x < y) arr[y] = arr[x];
    }
    arr[x] = temp; // 枢轴位置赋值为原来存储的
    quickSort(arr, l, x - 1);
    quickSort(arr, x + 1, r);
}

// unguarded_partition版本
void unguardedSort(int *arr, int l, int r)
{
    if(l >= r) return;
    int x = l, y = r, pivot = arr[l];
    // 在这里肯定 x < y
    while(x <= y)
    {
        // 找到 >= pivot的地方（注意，这里一定是<，否则有误）
        while(arr[x] > pivot) ++x;
        // 找到 <= pivot的地方（注意，这里一定是>，否则有误）
        while(arr[y] < pivot) --y;
        if(x <= y)
        {
            swap(arr[x], arr[y]);
            ++x, --y;
        }
    }

    // 到这里x左边的元素全部<=pivot，x右边的元素全部>=pivot
    // 注意，这里pivot枢轴元素可能离x（或者y）很远
    // 这算是无监督版quicksort的一个缺点？
    // printf("%d ", arr[x - 1]);
    unguardedSort(arr, l, x - 1);
    unguardedSort(arr, x, r);
}

int main()
{
    int a[10] = {1, 4, 231, 6, 213, 5, 5};
    quickSort(a, 0, 6);
    for(int i = 0; i < 7; ++i)
        printf("%d ", a[i]);
    return 0;
}