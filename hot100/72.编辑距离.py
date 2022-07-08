# 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数。
# 可选操作：插入 / 删除 / 替换一个字符。
# 编辑距离算法被数据科学家广泛应用，是用作机器翻译和语音识别评价标准的基本算法。

# Solution：dp
# 思路：dp[i][j] 代表串 s1[0...i] 和 s2[0...j] 之间的编辑距离。
# 定理 1：如果一个串是空串，那么编辑距离即另一个串的长度。
# 定理 2：对于 dp[i][j]，如串 s1 "horse", 串 s2 "ros"，有三种情况。
#     ① 串 "hors" 和 串 "ros" 之间编辑距离 + 1，即 dp[i][j] = dp[i-1][j] + 1
#     ② 串 "horse" 和串 "ro" 之间编辑距离 + 1，即 dp[i][j] = dp[i][j-1] + 1
#     ③ 串 "hors" 和 串 "ro" 之间编辑距离 + int(最后一个字符是否需要替换)
#        即 dp[i][j] = dp[i-1][j-1] + int(s1[i] == s2[j])
# 转移方程：dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1, 
#                        dp[i-1][j-1] + int(s1[i] != s2[j]))
# 边界条件：dp[0][j] = j, dp[i][0] = i。（对应定理1）
# 时间复杂度：O(mn)，空间复杂度：O(mn)
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        m, n = len(word1), len(word2)
        if m == 0 or n == 0:
            return m | n
        dp = [[101] * (n+1) for _ in range(m+1)]

        for i in range(m+1): # 0 代表空串
            dp[i][0] = i
        for i in range(n+1):
            dp[0][i] = i
        for i in range(1, m+1):
            for j in range(1, n+1):
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1
                # 这里是 i-1 和 j-1，因为 dp数组顾及空串，比原串大
                dp[i][j] = min(dp[i][j], dp[i-1][j-1] + int(word1[i-1] != word2[j-1]))
        return dp[-1][-1] # dp[m][n]

# 优化空间复杂度。
# 分析转移方程，dp[i][j] 和 dp[i-1][j], dp[i][j-1], dp[i-1][j-1] 有关
# 即和上，左，左上角元素有关。
# 因此，dp数组只需要存储每行即可。
# 对于 dp[j], dp[j-1]即左边的值（覆盖过），dp[j]即上面的值（未覆盖）。
# 左上角的元素使用一个额外变量 upper_left 来记录，upper_left随着 i 和 j的移动而移动。
# upper_left即 未覆盖过的 dp[j-1]
# 画图理解
#        r o s
#      0 1 2 3
#  dp --------
#   0| 0 1 2 3
# h 1| 1       <---- 从 i = 1, j = 1, dp[1] 开始填
# o 2| 2
# r 3| 3
# s 4| 4
# e 5| 5
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        m, n = len(word1), len(word2)
        dp = [101 for _ in range(n+1)] # 这里dp数组和字符串长度对应
        for i in range(n+1):
            dp[i] = i
        for i in range(1, m+1):
            upper_left = dp[0] # 未覆盖前的初始值
            dp[0] = i # 初始为每一行最左侧
            for j in range(1, n+1):
                tmp = dp[j] # 中间变量存储值
                dp[j] = min(dp[j], dp[j-1]) + 1
                dp[j] = min(dp[j], upper_left + int(word1[i-1] != word2[j-1]))
                upper_left = tmp
        return dp[n]