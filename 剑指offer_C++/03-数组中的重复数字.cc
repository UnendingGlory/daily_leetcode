#include "header.h"

// Solution 1: 哈希表法
// 时间复杂度O(1)
// 空间复杂度O(n)
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_map<int, bool> um;
        for (int num : nums) {
            if (um[num]) {
                return num;
            }
            um[num] = true;
        }
        return -1;
    }
};

// Solution 2:
// 利用数字范围在0到n-1这个条件
// 对于数组中的每个数字，如果排序好之后
// 数字i应该放在下标为i的地方
// 因此对于每一个下标为i的数字m，我们首先比较m == i
// 如果不是，就拿其和第m个数字比较
// 如果m == arr[m]，则说明找到了重复元素
// 如果m != arr[m]，则交换之，使得m == arr[m]
// 时间复杂度：o(n)
// 空间复杂度：o(1)
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            while (nums[i] != i) {
                if (nums[i] == nums[nums[i]]) {
                    return nums[i];
                } else {
                    swap(nums[i], nums[nums[i]]);
                }
            }
        }
        return -1;
    }
};