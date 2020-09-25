#include <bits/stdc++.h>
using namespace std;

// 错误
class Solution {
public:
    // dp问题,dp数组记录以当前数字做结尾的最大子序列的乘积
    // >= 1, =0则变为0，<0则变为负数
    // dp[i] = A[i], A[i] < 1
    // dp[i] = dp[i -  1] * A[i], A[i] >= 1
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int dp[n];
        dp[0] = nums[0];
        int ans = nums[0];
        for(int i = 1; i < n; ++i)
        {
            // 特殊情况判断
            if(dp[i - 1] <= 0)
            {
                if(nums[i] >= 0) dp[i] = nums[i];
                else dp[i] = dp[i - 1] * nums[i];
            }
            if(dp[i - 1] > 0)
            {
                if(nums[i] >= 0) dp[i] = dp[i - 1] * nums[i];
                else dp[i] = nums[i];
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }   
};

// 正确答案。。很迷
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxF = nums[0], minF = nums[0], ans = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            int mx = maxF, mn = minF;
            maxF = max(mx * nums[i], max(nums[i], mn * nums[i]));
            minF = min(mn * nums[i], min(nums[i], mx * nums[i]));
            ans = max(maxF, ans);
        }
        return ans;
    }
};