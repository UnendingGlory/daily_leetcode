#include "header.h"

// 连续子数组的最大和
// dp[i]代表前i个数的最大和
// 转移公式：dp[i] = max(dp[i - 1] + nums[i], nums[i])
// 初始化： dp[0] = nums[0]
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1);
        dp[0] = nums[0];
        int ans = nums[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};


