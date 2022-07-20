# 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
# 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
# 问总共有多少条不同的路径？

# Solution1: 经典dp。
# dp[i][j] 代表走到每个格子有多少不同的路径。
# 机器人只能向下或者向右走，
# 转移方程：dp[i][j] = dp[i-1][j] + dp[i][j-1]。
# 边界条件：dp[0][i] = dp[i][0] = 1。
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if i == 0 or j == 0:
                    dp[i][j] = 1
                else:
                    dp[i][j] = dp[i-1][j] + dp[i][j-1]
        return dp[m-1][n-1]

# Solution2: 组合数学。
# 一共需要移动 m - 1 + n - 1  = m + n - 2 次。
# 其中，向右移动 n - 1 次，向下移动 m - 1 次。
# 总路径条数即从 m + n - 2 中选 n - 1，即
# C(n - 1, m + n - 2) = (m + n - 2)! / [(n-1)! * (m-1)!]
#                     = (m + n - 2) * (m + n - 3) ... * n / (m-1)!
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        ans, j = 1, n
        for i in range(1, m):
            ans = ans * j / i
            j += 1
        return int(ans)
