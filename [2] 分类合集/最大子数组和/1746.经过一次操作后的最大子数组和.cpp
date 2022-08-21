#include "header.h"

// 你有一个整数数组 nums。你只能将一个元素 nums[i] 替换为 nums[i] * nums[i]。
// 返回替换后的最大子数组和。

// Solution: 动态规划。
// dp[i][0] 表示以 nums[i]为结尾，且没有替换的最大子数组和。
// dp[i][1] 表示以 nums[i]为结尾，且发生过一次替换后的最大子数组和。
//          则有两种可能性，一种是 [0 ... i-1]区间内的已经发生过替换。
//                       dp[i][1] = max(dp[i - 1][1] + nums[i], nums[i])
//                                = max(dp[i - 1][1], 0) + nums[i]
//                       一种是未发生过替换，替换位置 i。
//                       dp[i][1] = max(dp[i - 1][0] + nums[i] * nums[i], nums[i] * nums[i])
//                                = max(dp[i - 1][0], 0) + nums[i] * nums[i]
// 转移方程：dp[i][0] = max(dp[i - 1][0] + nums[i], nums[i]) = max(dp[i - 1][0], 0) + nums[i]
//         dp[i][1] = max(max(dp[i - 1][1], 0) + nums[i], max(dp[i - 1][0], 0) + nums[i] * nums[i])
// 边界条件：dp[0][0] = nums[0]; dp[0][1] = nums[0] * nums[0];
// 替换操作后结果一定更大，所以必定会发生替换。
// 最终结果：ans = max(ans, dp[i][1])
// 时间复杂度：O(n)，空间复杂度：O(n)。
class Solution {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int n = nums.size();
        int dp[n][2];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = nums[0];
        dp[0][1] = nums[0] * nums[0];
        int ans = dp[0][1];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i - 1][0], 0) + nums[i];
            dp[i][1] = max(max(dp[i - 1][1], 0) + nums[i], max(dp[i - 1][0], 0) + nums[i] * nums[i]);
            ans = max(ans, dp[i][1]);
        }
        return ans;
    }
};

// Solution：空间复杂度优化。
// 由于 dp[i] 只和 dp[i - 1]有关，因此采用两个滚动变量优化即可。
// 时间复杂度：O(n)，空间复杂度：O(1)。
class Solution {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int n = nums.size();
        int no_replaced = nums[0], replaced = nums[0] * nums[0];
        int ans = replaced;
        for (int i = 1; i < n; ++i) {
            // replaced优先修改，因为用到了覆盖之前的 no_replaced
            replaced = max(max(replaced, 0) + nums[i], max(no_replaced, 0) + nums[i] * nums[i]);
            no_replaced = max(no_replaced, 0) + nums[i];
            ans = max(ans, replaced);
        }
        return ans;
    }
};
