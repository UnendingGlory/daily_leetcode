from typing import List

# 动态规划经典问题。
# dp[i]代表第 i 天卖出该股票能获得的最大利润。
# 由于只能买入一次，卖出一次。
# 第 i 天可以选择 不卖，也可以选择卖。
# 当前日i最大的利润 = max(前i-1日最大的利润，当前日价格 - 前i-1日最低的价格)。
# 转移方程：dp[i] = max(dp[i-1], prices[i] - min(prices[0:i])
# 边界条件：dp[0] = 0

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        dp = [0 for _ in range(n)]
        ans, min_price = 0, prices[0]
        for i in range(1, n):
            dp[i] = max(dp[i-1], prices[i] - min_price)
            min_price = min(min_price, prices[i])
            ans = max(ans, dp[i])
        return ans
