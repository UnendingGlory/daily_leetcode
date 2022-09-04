#include "header.h"

// 给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
// 在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。
// 你也可以先购买，然后在 同一天 出售。
// 返回 你能获得的 最大 利润 。

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
