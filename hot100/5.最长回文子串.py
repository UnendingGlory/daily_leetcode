# 输入：s = "babad"
# 输出："bab" 或者 "aba"

# 子串是连续的
# 经典dp问题

# Solution1:
# 假设 dp[i][j]代表 S[i]->S[j]是否是回文子串
# 状态转移公式：
# dp[i][j] = dp[i+1][j-1], S[i] == S[j]
# dp[i][j] = 0, S[i] != S[j]
# 边界条件：
# dp[i][i] = 1，即子串长度为1
# dp[i][i+1] = 1 if S[i] == S[i+1] else 0，子串长度为2。
# 那么如何开始递推？
# 枚举长度为L的子串时需要计算长度为L - 2的子串，
# 由于已经知道了长度为1和2的，
# 所以可以先计算长为3的，再计算4的...，最后计算长度为n的
# 时间复杂度：O(n^2)
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        dp = [[False] * n for _ in range(n)] # py创建二维数组
        start, end = 0, 0 # 记录最长子串起始点和末端点

        for i in range(n): # 边界条件
            dp[i][i] = True
            if i != n-1 and s[i] == s[i+1]:
                dp[i][i+1] = True
                start = i
                end = i+1

        for k in range(3, n+1): # 开始递推
            # 枚举每个子串的起始端点为0，末端为 i + k - 1 <= n - 1，即 i <= n - k
            for i in range(n-k+1): 
                j = i + k - 1
                if s[i] == s[j] and dp[i+1][j-1]:
                    dp[i][j] = True
                    start, end = i, j
        return s[start:end+1]


# Solution2: 中心扩展法
# 反向dp
# 从长度为 1 和 2 出发，扩展子串，直至不能扩展为止
# 时间复杂度：O(n^2)
class Solution:
    def expandAroundCorner(self, s, i, j):
        # 从s[i...j]往两边扩展
        left, right = i-1, j+1
        while left >= 0 and right < len(s) and s[left] == s[right]:
            left -= 1
            right += 1
        return left + 1, right - 1

    def longestPalindrome(self, s: str) -> str:
        start, end = 0, 0
        for i in range(len(s)): # 对每一个中心
            left1, right1 = self.expandAroundCorner(s, i, i) # 长度为1
            if right1 - left1 > end - start:
                start, end = left1, right1

            if i != len(s) - 1 and s[i] == s[i+1]:
                left2, right2 = self.expandAroundCorner(s, i, i+1) # 长度为2
                if right2 - left2 > end - start:
                    start, end = left2, right2
        return s[start:end+1]
