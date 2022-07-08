from typing import List
# 如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
# 计算出一夜之间能投到的最多金额。

# 即不能选择相邻元素，求能取得的元素的最大和。
# 动态规划。
# 假设 dp[i] 代表偷窃到第i个位置能取得的最大和，那么此时有两个选择。
# 1. 偷窃第 i 个位置，那么第 i-1 个位置就不能偷窃，即偷窃位置 i-2 和 i
# 2. 不偷窃第 i 个位置，那么能偷窃到的最大值就是 第 i - 1 个位置的
# 第 i 个位置能偷窃的最大值即这两种情况的最大值。
# 动态转移方程：dp[i] = max(dp[i-2] + nums[i], dp[i-1])
# 边界条件：dp[0] = nums[0]
class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return nums[0]
        dp = [0 for i in range(n)]
        dp[0], dp[1] = nums[0], max(nums[0], nums[1]) # nums.len >= 1
        for i in range(2, n):
            dp[i] = max(dp[i-2] + nums[i], dp[i-1])
        return dp[n-1]
