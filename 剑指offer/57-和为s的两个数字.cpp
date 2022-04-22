#include "header.h"


// 两数之和中可以使用哈希表存储target - x，两次遍历即可
// 此题与两数之和不同的是，该题中数组为排序数组
// 可以使用双指针法直接操作
// sum小了左指针右移，大了右指针左移
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1, sum;
        while (l < r) {
            sum = nums[l] + nums[r];
            if (sum < target) {
                ++l;
            } else if (sum > target) {
                --r;
            }
            else {
                return vector<int> {nums[l], nums[r]};
            } 
        }
        return {};
    }
};
