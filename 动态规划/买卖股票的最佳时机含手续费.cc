#include "header.h"

// dp[0][_]代表操作完后没有股票能赚多少
// dp[1][i]代表操作完后有股票能赚多少
// 最后没有股票的状态一定大于有股票的状态
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> dp(2, vector<int>(n));
        dp[0][0] = 0, dp[1][0] = -prices[0];
        for (int i = 1; i < n; ++i) {
            // 如果手上原本就没有股票，那就不操作，如果有就卖出
            dp[0][i] = max(dp[0][i - 1], dp[1][i - 1] + prices[i] - fee);
            // 如果手上原本有股票，可以保留，如果没有，就买入
            dp[1][i] = max(dp[1][i - 1], dp[0][i - 1] - prices[i]);
        }
        return max(dp[0][n - 1], dp[1][n - 1]);
    }
};

// 由于每一刻的状态只和上一时刻有关
// 空间可以优化成o(1)
// 用两个变量保存dp[0][i]和dp[1][i]即可
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int max_no = 0, max_has = -prices[0];
        for (int i = 1; i < n; ++i) {
            max_no = max(max_no, max_has + prices[i] - fee);
            max_has = max(max_has, max_no - prices[i]);
        }
        return max_no;
    }
};