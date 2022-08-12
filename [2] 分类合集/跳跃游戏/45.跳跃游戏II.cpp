#include "header.h"

// 给你一个非负整数数组 nums ，你最初位于数组的第一个位置。
// 数组中的每个元素代表你在该位置可以跳跃的最大长度。
// 你的目标是使用最少的跳跃次数到达数组的最后一个位置。
// 假设你总是可以到达数组的最后一个位置。
// 返回最少需要的跳跃次数。

// Solution: 贪心算法。
// 正向遍历，初始位置从 0出发。
// 贪心地进行正向查找，每次找到可到达的最远位置，就可以在线性时间内得到最少的跳跃次数。
// 每一步在[i, i + nums[i]]中选择最远的作为下一跳的起跳点。
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        // start为下一步起跳位置
        int start = 0, end = 1; 
        while (end < n) {
            int maxPos = 0; // 当前起跳点能够到达的最远位置
            for (int i = start; i < end; i++) {
                maxPos = max(maxPos, i + nums[i]);
            }
            start = end;
            end = maxPos + 1;
            ++ans;
        }
        return ans;
    }
};

// 优化：一次循环处理。
class Solution {
public:
    int jump(vector<int>& nums)
    {
        int ans = 0;
        int end = 0;
        int maxPos = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            maxPos = max(nums[i] + i, maxPos);
            // 如果到达了能跳到的最远距离，步数+1，同时更新该距离
            if (i == end) {
                end = maxPos;
                ans++;
            }
        }
        return ans;
    }
};
