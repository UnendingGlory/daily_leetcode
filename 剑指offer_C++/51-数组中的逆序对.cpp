#include "header.h"

// 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。
// 输入一个数组，求出这个数组中的逆序对的总数


// 暴力：双层for循环，超时
// 对归并排序的过程中计算逆序对
// [7, 5, 6, 4]
// [7] [5] [6] [4]  逆序对：0
// [7, 5]  [6, 4]   逆序对：2
// [7, 5, 6, 4]     逆序对：2 + 1
// 总的逆序对：5

// 如果左侧序列指针指向的数比右边指针第一个大
// 那么贡献为左侧指针到左侧序列到底部的长度
class Solution {
    int ans;
public:
    void merge(vector<int> &nums, int l, int mid, int r) { // 合并两个有序序列
        // temp存放合并后的数组
        vector<int> temp(r - l + 1);
        int idx = 0, i = l, j = mid + 1;

        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) {
                temp[idx] = nums[i];
                ++idx, ++i;
            } else {
                ans += (mid - i + 1); // 左侧指针到最右侧
                temp[idx] = nums[j];
                ++idx, ++j;
            }
        }
        while (i <= mid) {
            temp[idx] = nums[i];
            ++idx, ++i;
        }

        while (j <= r) {
            temp[idx] = nums[j];
            ++idx, ++j;
        }
        // 将temp拷贝到原数组
        for (i = 0; i < r - l + 1; ++i) {
            nums[l + i] = temp[i];
        }
    }

    void mergeSort(vector<int>& nums, int l, int r){
        if (l >= r) return;
        int mid = l + ((r - l) >> 1);
        mergeSort(nums, l, mid);
        mergeSort(nums, mid+1, r);
        merge(nums, l, mid, r);
    }

    int reversePairs(vector<int>& nums) {
        ans = 0;
        mergeSort(nums, 0, nums.size() - 1);
        return ans;
    }
};
