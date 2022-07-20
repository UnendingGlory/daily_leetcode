#include "header.h"


// 统计一个数字在排序数组中出现的次数，注意，数字可能重复。
// Solution1: 直接遍历
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int ans = 0;
        for (int &i: nums) {
            if (target == i) {
                ++ans;
            }
        }
        return ans;
    }
};


// Solution2: 二分 + 双指针
// 先二分到指定数字，再从两边双指针统计
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1, mid = -1;
        while (l <= r) {
            mid = l + ((r - l) >> 1);
            if (nums[mid] > target) { // 这里要写mid - 1
                r = mid-1;
            } else if (nums[mid] == target) {
                break;
            } else { // 这里要写mid + 1
                l = mid+1;
            }
        }
        if (mid == -1) return 0;
        int ans = 0;
        for (l = mid; l >= 0 && nums[l] == target; --l) ++ans;
        for (r = mid+1; r < nums.size() && nums[r] == target; ++r) ++ans;
        return ans;
    }
};


// Solution3: 二分
// 找到数组中第一个等于target的位置，记为leftIdx
// 再找到数组中第一个大于target的位置减一，记为rightIdx
// 结果即为rightIdx - leftIdx + 1
// 注意边界条件
class Solution {
public:
    // greater即是否是相等查找，还是大于的查找
    int binarySearch(vector<int>& nums, int target, bool greater) {
        int l = 0, r = nums.size() - 1, mid, ans = nums.size();  // ans设置为最后一个
        while (l <= r) {
            mid = l + ((r - l) >> 1);
            // 查找第一个大于的二分模板 以及 查找第一个大于等于的二分模板
            if (nums[mid] > target || (!greater && nums[mid] >= target)) {
                r = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
    
    int search(vector<int>& nums, int target) {
        int leftIdx = binarySearch(nums, target, false);
        int rightIdx = binarySearch(nums, target, true) - 1;
        return rightIdx - leftIdx + 1;
    }
};

