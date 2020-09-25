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

int main()
{
    return 0;
}