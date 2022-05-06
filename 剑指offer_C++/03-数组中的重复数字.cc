#include "header.h"

// Solution 1: 哈希表法
// 时间复杂度O(n)
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
// 利用数字范围在 0 到 n-1 这个条件
// 对于数组中的每个数字，如果排序好之后
// 数字i应该放在下标为i的地方

// 举例：
// nums:  2 3 1 0 2 5 3 
// 排序后: 0 1 2 3 4 5 6

// 对原数组进行遍历。
// 遍历中，第一次遇到数字 x时，将其交换至索引 x 处。
// 而当第二次遇到数字 x 时，一定有 nums[x] = x ，此时即可得到一组重复数字。

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