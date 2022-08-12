#include "header.h"

// 即在买入股票之前必须先卖出。
// 假设 dp[i][0]代表第i天结束时，持有一支股票
//      dp[i][1]代表第i天结束时，未持有股票
// 状态转移：dp[i][0] = max(dp[i-1][0], dp[i-1][1] - prices[i])
//         dp[i][1] = max(dp[i-1][1], dp[i-1][0] + prices[i])
// 边界条件：dp[0][0] = -prices[0], dp[0][1] = 0
// 答案：dp[n-1][1]

// 时间复杂度：O(n^2)，空间复杂度：O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = -prices[0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] - prices[i]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] + prices[i]);
        }
        return dp[n-1][1];
    }
};

// 空间复杂度优化，使用两个变量存储即可。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int last0 = -prices[0], last1 = 0;
        int cur0, cur1;
        for (int i = 1; i < prices.size(); ++i) {
            cur0 = max(last0, last1 - prices[i]);
            cur1 = max(last1, last0 + prices[i]);
            last0 = cur0;
            last1 = cur1;
        }
        return last1;
    }
};
