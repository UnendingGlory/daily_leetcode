#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 返回在数组中的下标，双指针法
    int Patition(int left, int right, vector<int>& nums)
    {
        int temp = nums[left]; // 选取第一个元素作为枢轴
        while(left < right) // 未相遇
        {
            while(left < right && nums[right] > temp) --right;
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
        // 右边找比枢轴小的，注意x<y的判断
        while(x < y && arr[y] >= temp) --y;
        // 找到了则交换
        if(x < y) arr[x] = arr[y];
        while(x < y && arr[x] <= temp) ++x;
        if(x < y) arr[y] = arr[x];
    }
    arr[x] = temp; // 枢轴位置赋值为原来存储的
    quickSort(arr, l, x - 1);
    quickSort(arr, x + 1, r);
    return;
}

int main()
{
    int a[10] = {1, 4, 6, 5, 3};
    quickSort(a, 0, 4);
    for(int i = 0; i < 5; ++i)
        printf("%d ", a[i]);
    return 0;
}