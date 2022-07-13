from typing import List
# 动态规划经典问题。
# dp[i]表示以i下标元素为结尾的子序列的最长递增序列长度。
# 那么 nums[i]可以自己组成一个序列，也可以选择和前面的元素组成一个序列。
# 那么对于下标 0到 j-1，如果 nums[j] < nums[i]，那么下标[...j i]对应的是一个最长递增子序列。
# 状态转移方程：dp[i] = max(dp[0...j-1]) + 1 or dp[i] = 1。
# 边界条件：dp[0] = 1
# 时间复杂度：O(n^2)

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [0 for _ in range(n)]
        ans = 0
        for i in range(1, n):
            dp[i] = 1
            for j in range(0, i):
                if nums[j] < nums[i] and dp[j] + 1 > dp[i]:
                    dp[i] = dp[j] + 1
            ans = max(ans, dp[i])
        return ans
