from typing import List

# 给定一个包含非负整数的 m x n 网格 grid，请找出一条从左上角到右下角的路径，
# 使得路径上的数字总和为最小。

# Solution: dp。
# 每次只能往右或者往下。
# 状态转移方程：dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + nums[i][j]。
# 边界条件：dp[0][i] = dp[i][0] = 0。
class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        row, col = len(grid), len(grid[0])
        dp = [[0] * col for _ in range(row)]
        dp[0][0] = grid[0][0]
        for i in range(1, row):
            dp[i][0] = dp[i-1][0] + grid[i][0]
        for i in range(1, col):
            dp[0][i] = dp[0][i-1] + grid[0][i]
        for i in range(1, row):
            for j in range(1, col):
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
        return dp[-1][-1]
