#include "header.h"

// 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
// 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。
// 设计一个算法来计算你所能获取的最大利润。

// Solution1: dp。
// dp[i]表示第i天结束时能获得的最大利润。
// 记录i天前的历史最低点，然后在每一天考虑这么一个问题：
// 如果我是在历史最低点买进的，那么我今天卖出能赚多少钱？
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> dp(n);
        int lowest = prices[0];
        for (int i = 1; i < n; ++i) {
            lowest = min(prices[i], lowest);
            dp[i] = max(dp[i - 1], prices[i] - lowest);
        }
        return dp[n - 1];
    }
};

// Solution2: 单调栈。
// 求某个数与其右边最大的数的差值。
// 从左到右遍历数组，栈底到栈顶单调递减。
// 数组元素 prices[i]与栈顶比较，如果小就入栈，大就更新答案。
// 由于是最大，所以这里没有出栈操作。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        stack<int> s;
        int ans = 0;
        s.push(prices[0]);
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] < s.top()) {
                s.push(prices[i]);
            } else {
                ans = max(ans, prices[i] - s.top());
            }
        }
        return ans;
    }
};
