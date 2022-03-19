#include "header.h"
using namespace std;

/* 动态规划经典问题
 * dp[i]表示以下标i的数组元素为结尾的序列的最大和
 * 则dp[i]要么只有自己一个元素，要么会带上前面一个元素的dp值
 * 状态转移方程:dp[i] = max(dp[i - 1] + A[i], A[i])
 * 则最后整个序列的最大子序和就是dp[0] - dp[i]中最大的那个
 * 时间复杂度:o(n)
 */

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int dp[n], ans = nums[0];
        dp[0] = nums[0];
        // 一遍遍历
        for(int i = 1; i < nums.size(); ++i)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};