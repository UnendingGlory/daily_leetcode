#include "header.h"

// 给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
// 数组中的每个元素代表你在该位置可以跳跃的最大长度。
// 判断你是否能够到达最后一个下标。

// Solution: 贪心算法。
// 如果位置 x能到达数组最后一个位置，那么 x + nums[x]也可以到达。
// 动态维护一个变量 mostright，判断 mostright是否到达数组边界。
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int mostright = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            // i <= mostright 代表能够到达位置 i
            if (i <= mostright && nums[i] + i >= mostright) {
                mostright = nums[i] + i;
                if (mostright >= n - 1) {
                    return true;
                }
            }
        }
        return false;
    }
};