#include "header.h"

// 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
// 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票，这一点很重要）。

// 同样也是动态规划。股票问题的核心就是考虑 [第 i天结束时]的几种状态。
// 首先是设计状态。如果最多能完成两笔交易，那么 [第 i天结束时] 总共有以下情况：
// 1. 手上没有股票，从未买入 
// 2. 手上有一只股票，且未买入第二只股票 buy_one
// 3. 手上有一只股票且卖出，未买入第二只股票 sell_one
// 4. 手上第一只股票卖出，买入了第二只股票 buy_two
// 5. 两只股票均卖出 sell_two
// 第一个状态利润显然为 0，不予考虑。
// 记录 2.3.4.5状态 分别为 buy_one, sell_one, buy_two, sell_two
// 那么我们要考虑的状态转移方程即通过第 i - 1天的四种状态得到第 i天的状态。

// 对于 buy_one，第 i天我们可以不操作，也可以在第 i天买入一只股票。
//              buy_one = max(buy_one', -prices[i])
// 对于 sell_one，第 i天之前可能卖出，什么也不操作，或者 在 第 i天卖出
//              sell_one = max(sell_one', buy_one' + prices[i])
// 对于 buy_two，第 i天之前可能已经买入了第二只股票，什么也不操作，或者在第 i天买入第二只股票。
//              buy_two = max(buy_two, sell_one' - prices[i])
// 对于 sell_two，第 i天之前可能已经卖出了第二只股票，什么也不操作，或者在第 i天卖出第二只股票。
//              sell_two = max(sell_two', buy_two' + prices[i])
// 边界条件：第 0天结束时，buy_one = -prices[0], sell_one = 0, buy_two = 0, sell_two = 0
// 返回答案：max(sell_one, sell_two)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // buy_two 为同一天买入后卖出再买入
        int buy_one = -prices[0], sell_one = 0, buy_two = -prices[0], sell_two = 0;
        int pre_buy_one, pre_sell_one, pre_buy_two, pre_sell_two;
        for (int i = 1; i < n; ++i) {
            pre_buy_one = buy_one;
            pre_sell_one = sell_one;
            pre_buy_two = buy_two;
            pre_sell_two = sell_two;
            buy_one = max(pre_buy_one, -prices[i]);
            sell_one = max(pre_sell_one, pre_buy_one + prices[i]);
            buy_two = max(pre_buy_two, pre_sell_one - prices[i]);
            sell_two = max(pre_sell_two, pre_buy_two + prices[i]);
        }
        return max(sell_one, sell_two);
    }
};