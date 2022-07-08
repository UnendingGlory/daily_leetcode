# 回忆85题，最大矩形，使用 left[i][j] 记录 matrix[i][j] 左侧元素的 1 的个数。
# 两种solution，最优方法是转换为84柱状图中最大矩形，使用单调栈。
from typing import List

# 该题求解的是最大正方形。
# 求解最大正方形，只需要求解得到最大边长即可。
# Solution1：暴力法。
# 对二维矩阵进行遍历，假设遍历到位置 matrix[i][j] 为 1，
# 假设以该结点为正方形的左上角，那么正方形最大的边长 maxSide 为 min(row - i + 1, col - j + 1)。
# 那么我们遍历边长 1 到 maxSide，每次遍历添加右边一列和下方一行即可。
# 假设遍历到的边长为 k, 首先判断 matrix[i+k-1][j+k-1]是否为1。
# 即以 matrix[i][j] 为左上角，边长为 k 的正方形的右下角是否为 1。
# 如果不为1，直接跳出遍历边长的循环。
# 如果为1，再检查行和列是否全为 1。
# 时间复杂度：O(mn * min(m, n)^2)，空间复杂度：O(1)。
# 会超时。
class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        row, col = len(matrix), len(matrix[0])
        ans = 0
        for i in range(row):
            for j in range(col):
                if matrix[i][j] == '1':
                    maxSide = max(1, maxSide)
                    currentMaxSide = min(row - i, col - j)
                     # currentMaxSide其实多 1
                    for k in range(1, currentMaxSide):
                        # 判断新增的一行一列的右下角
                        if matrix[i+k][j+k] == '0':
                            break
                        flag = True
                        # 判断新增的一行一列
                        for m in range(k):
                            if matrix[i+k][j+m] == '0' or matrix[i+m][j+k] == '0':
                                flag = False
                                break
                        if flag:
                            maxSide = max(maxSide, k+1) # 包括 matrix[i][j]自己
                        else:
                            break
        ans = maxSide * maxSide
        return ans


# Solution2：动态规划。
# 降低时间复杂度，方法1中包含大量的重复判断，以及计算边的过程。
# 考虑使用动态规划进行优化，如何优化呢？
# 假设 dp[i][j] 表示以 (i, j) 为右下角，且只包含 '1' 的正方形的边长的最大值。
# 分情况讨论：
# 如果该位置的值为 '0'，那么 dp[i][j] 必然为 0。
# 如果该位置的值为 '1'，那么 dp[i][j] 的值为 dp[i-1][j], dp[i-1][j-1], dp[i][j-1]中的最小值 + 1。
# 证明：反证法，如果选定的是 dp[i][j] = dp[i-1][j]
# 那么 dp[i-1][j] 比 dp[i-1][j-1] 和 dp[i][j-1] 均小，即边长最小。
# 图解，对于下图，dp[3][3]的值由 dp[2][3], dp[3][2], dp[2][2]决定。
#           1 1 1 0
#           1 1 1 1
#           1 1 1 1
#           0 1 1 
# dp[2][2] = 3, dp[2][3] = 2, dp[3][2] = 2。
# 可能看出，如果 matrix[i][j] 为 '1'，那么 dp[3][3] 为 2 + 1 = 3。
# 时间复杂度：O(mn), 空间复杂度：O(mn)。

# 转移方程：dp[i][j] = min(dp[i-1][j], dp[i-1][j-1], dp[i][j-1]) + 1 if matrix[i][j] == '1' else 0;
# 边界条件：dp[0][j] = 1 if matrix[0][j] = '1'; dp[i][0] if matrix[i][0] = '1;
class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        row, col = len(matrix), len(matrix[0])
        ans, maxSide = 0, 0
        dp = [[0] * col for _ in range(row)]
        for i in range(row):
            for j in range(col):
                if matrix[i][j] == '1':
                    if i == 0 or j == 0:
                        dp[i][j] = 1
                    else:
                        dp[i][j] = min(dp[i-1][j], dp[i-1][j-1], dp[i][j-1]) + 1
                    maxSide = max(maxSide, dp[i][j])
        ans = maxSide * maxSide
        return ans
        