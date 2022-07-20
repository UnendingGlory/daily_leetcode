# 需要 n 阶你才能到达楼顶。
# 每次可以爬 1 或 2 个台阶。有多少种不同的方法可以爬到楼顶呢？

# Solution: 动态规划。
# 斐波那契问题动态规划。
# 使用滚动变量节约空间。

# 假设 dp[i] 代表到达第 n 阶时有几种方法。
# 状态转移方程：dp[i] = dp[i-1] + dp[i-2]
# 边界条件：dp[0] = dp[1] = 1
class Solution:
    def climbStairs(self, n: int) -> int:
        if n == 0 or n == 1:
            return 1
        a, b, c = 1, 1, 0
        for i in range(2, n+1):
            c = a + b
            a = b
            b = c
        return c

if __name__ == "__main__":
    s = Solution()
    ans = []
    for i in range(1, 46):
        ans.append(s.climbStairs(i))
    print(ans)
