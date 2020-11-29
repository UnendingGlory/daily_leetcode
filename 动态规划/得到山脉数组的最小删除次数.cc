#include "header.h"

/**
 * 枚举每一个位置作为山形最高点，就需要计算该位置的左右两边最少需要删除多少个点。
 * 以计算左边为例，要计算位置i左边最少删除个数f[i]，就要从i-1的位置向左遍历（指针记为j）直到头，
 * 每当遇到nums[j] < nums[i]的位置j，就用以下两个情况的最小值更新f[i]的答案
 * f[i]，表示保留原始情况，不更新
 * f[j] + i - j - 1，表示利用 f[j]的结果再加上夹在j和i之间所有的点都删除的总数
 * 类似地处理每个元素右边最少删除个数g
 * 边界条件：初始化f和g为其左边或右边点的个数，代表将左边或者右边的所有点全部删掉
 * 该处理的复杂度为O(n^2)
 * 之后同时遍历f和g，返回最小f + g
 */

class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n), g(n);
        for(int i = 0; i < n; ++i)
        {
            f[i] = i, g[i] = n - i - 1;
        }
        for(int i = 1; i < n; ++i)
        {
            for(int j = i - 1; j >= 0; --j)
                if(nums[j] < nums[i])
                    f[i] = min(f[i], f[j] + i - j - 1);
        }
        for(int i = n - 2; i >= 0; --i)
        {
            for(int j = i + 1; j < n; ++j)
                if(nums[j] < nums[i])
                    g[i] = min(g[i], g[j] + j - i - 1);
        }
        int ans = INT_MAX;
        // 山峰不能是两端
        for(int i = 1; i < n - 1; ++i)
        {
            ans = min(ans, f[i] + g[i]);
        }
        return ans;
    }
};