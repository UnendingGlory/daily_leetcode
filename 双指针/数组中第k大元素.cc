#include "header.h"

// 类似STL库中的nth element算法
// 由于在快排中partition操作每次会放置一个元素，左边比其小，右边比其大
// partition过后这个元素的位置便不会改变
// 因此如果某个元素partition操作后处于第k个位置则就是我们要找的元素
// 所以如果partition后枢轴的位置比目标位置大则递归左边区间
// 否则递归区间

// 此题不能用unguarded_partition，因为unguarded_partition不能获取枢轴的位置
// 应该用最常见的partition
// 注意这里应该是从大到小排序，所以比较顺序相反

// 但是这里没有考虑到如果有多个元素相等的情况

class Solution {
public:

    int partition(vector<int> &nums, int l, int r) {
        if(l <= r) {
            int x = l, y = r, pivot = nums[l];
            while (x <= y) {
                while(nums[x] >= pivot) ++x;
                std::swap(nums[x], pivot);
                while(nums[y] <= pivot) --y;
                std::swap(nums[y], pivot);
            }
            // x为枢轴元素放置的位置
            nums[x] = pivot;
            return x;
        }
    }

    int findKthLargest(vector<int>& nums, int k) {

    }
};