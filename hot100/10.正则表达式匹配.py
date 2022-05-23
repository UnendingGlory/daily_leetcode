# https://leetcode.cn/problems/regular-expression-matching/solution/liang-chong-si-lu-di-gui-dong-tai-gui-hu-gh69/

# Solution1: 往后看，记忆化递归
# 双指针分别指向两个字符串，'.'可以匹配任意字符

# 主要需要处理的就是 a* 这种情况
# a* 即可以当作0个，也可以当作多个a

# 递归边界：i == len(s), j == len(p)
# dfs(i, j) = dfs(i+1, j), p[j+1] = '*' 且 s[i] = p[j] 即匹配多次

# dfs(i, j) = dfs(i, j+2), p[j+1] = '*' 且 s[i] = p[j] 即匹配0次
# dfs(i, j) = dfs(i, j+2), p[j+1] = '*' 且 s[i] != p[j] 不匹配直接跳过
# 合并成：
# dfs(i, j) = dfs(i, j+2), p[j+1] = '*'

# dfs(i, j) = dfs(i+1, j+1), p[j+1] != '*' 且 p[j] == s[i]
# dfs(i, j) = False, p[j+1] != '*' 且 p[j] != s[i]

# 纯递归可能超时，加一个数组记忆递归结果

class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        memo = [[-1 for _ in range(len(p))] for _ in range(len(s)+1)] # -1表示未记录
        def dfs(i, j):
            if j == len(p): # 模式串扫描完
                return i == len(s)
            if memo[i][j] != -1: # 这里有可能 i = len(s)，所以memo中i的维度要多一维
                return memo[i][j]
            
            # 检查s[i]是否能匹配，合并写法
            matchable = i < len(s) and p[j] in {s[i], '.'} 

            if j != len(p) - 1 and p[j+1] == '*': # 如果模式串下一个是 *
                # 匹配多次 或者 匹配0次
                memo[i][j] = (matchable and dfs(i+1, j)) or dfs(i, j+2)
            else: # 如果模式串下一个不是 '*'
                memo[i][j] = matchable and dfs(i+1, j+1)

            return memo[i][j]

        return dfs(0, 0)


# Solution2: 向前看，动态规划，即递归的逆过程
# dp[i][j] 代表 s 的前i个字符和 p的前j 个字符是否匹配
# 即s[0...i-1] 和 p[0...j-1] 是否匹配

# 分析：
# 若 p[j-1] 为 '*', 则考虑匹配次数
# 1. s[i-1]可被匹配，即 p[j-2] = s[i-1]，或者 p[j-2] = '.'，匹配多次或0次
# 2. s[i-1]不可被匹配，则匹配0次
# 若 p[j-1] 不为'*', 则直接匹配 s[i-1] 和 p[j-1]

# 状态转移方程：
# dp[i][j] = dp[i-1][j], p[j-1] = '*'且 s[i-1] = p[j-2]，匹配多次
# dp[i][j] = dp[i][j-2], p[j-1] = '*'且 s[i-1] = p[j-2]，匹配0次
# 可以合并为：
# dp[i][j] = dp[i][j-2] or dp[i][j-2], p[j-1] = '*'

# dp[i][j] = dp[i][j-2], p[j-1] = '*'且 s[i-1] != p[j-2]

# dp[i][j] = dp[i-1][j-1], p[j-1] != '*'且 s[i-1] = p[j-1]匹配

# 边界条件：
# s 和 p均为空时必匹配
# 若s为空，p只有全为 * 才匹配
# dp[0][0] = True
# dp[0][j] = (p[j-1] = '*' and dp[0][j-2]), j为偶数, 比如s为0，p为1肯定不匹配

class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        dp = [[False for _ in range(len(p)+1)] for _ in range(len(s)+1)]
        dp[0][0] = True

        for i in range(2, len(p)+1, 2):  # 边界条件
            dp[0][i] = (p[i-1] == '*' and dp[0][i-2])

        for i in range(1, len(s)+1):
            for j in range(1, len(p)+1):
                if p[j-1] == '*': # = '*'
                    if p[j-2] == s[i-1] or p[j-2] == '.':
                        dp[i][j] = dp[i-1][j] or dp[i][j-2]
                    else:# 不匹配
                        dp[i][j] = dp[i][j-2]
                if p[j-1] == s[i-1] or p[j-1] == '.': # 其他情况下匹配
                    dp[i][j] = dp[i-1][j-1]
        return dp[-1][-1]
