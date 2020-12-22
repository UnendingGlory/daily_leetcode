#include "../header.h"


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
		// 2 * n
		vector<vector<int>> dp(2, vector<int>(n));
        // 0代表操作完没有股票的状态，1代表操作完有股票的状态
		// dp[i][0]，若i时刻没有股票，则什么都不做，若i时刻有股票，则卖出
		// dp[i][0] = max{dp[i - 1][0], dp[i - 1][1] + prices[i] }
		// dp[i][1]，若i时刻有股票，则i时刻什么都不做，若i时刻没有股票，则i时刻买进
		// dp[i][1] = max{dp[i - 1][1], dp[i - 1][0] - prices[i] }
		// 最后没有股票的收益一定大于有股票的收益
		dp[0][0] = 0; dp[0][1] = -prices[0];
		for(int i = 1; i < n; ++i)
		{
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
		}
		return dp[n - 1][0];
    }
};

// 注意每一天的状态只与前一天有关，所以可以进行空间优化
// 用两个变量保存dp[i - 1][0]和dp[i - 1][1]即可
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
		// 2 * n
		vector<vector<int>> dp(2, vector<int>(n));
		// last1保存dp[i - 1][0], last2保存dp[i - 1][1]
		int last1 = 0, last2 = -prices[0];
		for(int i = 1; i < n; ++i)
		{
			last1 = max(last1, last2 + prices[i]);
			last2 = max(last2, last1 - prices[i]);
		}
		return last1;
    }
};