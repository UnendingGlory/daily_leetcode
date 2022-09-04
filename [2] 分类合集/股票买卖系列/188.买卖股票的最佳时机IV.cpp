#include "header.h"

// 给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。
// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
// 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票，这一点很重要）。

// 动态规划，股票问题的核心就是考虑 [在第 i天结束时的状态]
// 对于 prices[0...i]，考虑 [第 i天结束时]的状态。
// 使用 buy[i][j]表示第 i天结束时，恰好进行 j笔交易，并且手上持有一支股票的最大利润。
//    sell[i][j]表示第 i天结束时，恰好进行 j笔交易，并且手上没有股票的最大利润。
//    买入又卖出才算一笔交易，所以交易完成由卖出决定。
// 状态转移方程：
// buy[i][j]：第 i天结束时，可以什么都不操作，也可以之前没有股票，买入一支股票。
//            buy[i][j] = max(buy[i - 1][j], sell[i - 1][j] - prices[i])
// sell[i][j]：第 i天结束时，可以什么都不操作，也可以之前持有一支股票，卖出该股票（算一次交易）。
//            sell[i][j] = max(sell[i - 1][j], buy[i - 1][j - 1] + prices[i])

// 边界条件：第 0天结束时，
// 对于 buy，最多买入一支股票，因此 buy[0][0] = -prices[i], buy[0][1..k] = -INF。
// 对于 sell，均为 0。且 sell[i][0]肯定为 0，因此 j = 0 sell可以略过。
// 最终答案：max(sell[n - 1][1...k])
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        const int INF = 1e9;
        vector<vector<int>> buy(n, vector<int>(k + 1, -INF));
        vector<vector<int>> sell(n, vector<int>(k + 1, 0));
        buy[0][0] = -prices[0];
        for (int i = 1; i < n; ++i) {
            buy[i][0] = max(buy[i - 1][0], sell[i - 1][0] - prices[i]);
            for (int j = 1; j <= k; ++j) { // 一个交易都没肯定为 0
                buy[i][j] = max(buy[i - 1][j], sell[i - 1][j] - prices[i]);
                sell[i][j] = max(sell[i - 1][j], buy[i - 1][j - 1] + prices[i]);
            }
        }
        return *max_element(sell[n - 1].begin(), sell[n - 1].end());
    }
};

// 空间复杂度优化： buy[i], sell[i]均只与 i - 1相关。
// 因此可以使用一维滚动数组进行优化。
// 时间复杂度优化：数组长度为 n，最多只可能完成 n / 2笔交易（买进一次，卖出一次）。
//              因此可以取 k = min(k, n / 2);
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        const int INF = 1e9;
        k = min(k, n / 2);
        vector<int> buy(k + 1, -INF), pre_buy;
        vector<int> sell(k + 1, 0), pre_sell;
        buy[0] = -prices[0];
        for (int i = 1; i < n; ++i) {
            pre_buy = buy, pre_sell = sell;
            buy[0] = max(pre_buy[0], pre_sell[0] - prices[i]);
            for (int j = 1; j <= k; ++j) { // 一个交易都没肯定为 0
                buy[j] = max(pre_buy[j], pre_sell[j] - prices[i]);
                sell[j] = max(pre_sell[j], pre_buy[j - 1] + prices[i]);
            }
        }
        return *max_element(sell.begin(), sell.end());
    }
};
