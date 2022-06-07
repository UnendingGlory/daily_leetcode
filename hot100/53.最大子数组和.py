from typing import List

# dp问题
# 动态转移方程：dp[i] = max(dp[i-1] + nums[i], nums[i])
# 即是接上一个 dp 数组的尾部，还是从这个数开始
# 边界条件: dp[0] = nums[0]
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [0 for _ in range(n)]
        ans = -1e-7
        for i in range(1, n):
            dp[i] = max(dp[i-1] + nums[i], nums[i])
            ans = max(ans, dp[i])
        return ans
