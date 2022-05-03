#include "header.h"


// 买卖该股票一次可能获得的最大利润是多少？
// 暴力：O(n^2)

// Solution: 动态规划
// dp[i] 代表 前 i 日的最大利润
// 转移方程：当前日i最大的利润 = max(前i-1日最大的利润，当前日价格-前i-1日最低的价格)
// dp[i] = max(dp[i-1], prices[i] - min(prices[0:i-1]))
// 边界条件：dp[0] = 0
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n == 0) return 0;
        vector<int>dp(n);
        int min_cost = prices[0];
        for (int i = 1; i < n; ++i) {
            min_cost = min(prices[i], min_cost);
            dp[i] = max(dp[i - 1], prices[i] - min_cost);
        }
        return dp[n - 1];
    }
};

