# 给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。

# Solution1：动态规划。
# 假设 n 个节点存在二叉排序树的个数是 G(n)，令 f(i) 为以 i 为根的二叉搜索树的个数。
# 1. 那么 G(n) = f(1) + f(2) + ... + f(n)，边界情况：G(0) = 1, G(1) = 1。
# 2. 由于是二叉排序树，所以 若以 i 为根，左侧元素均小于i，右侧元素均大于i。
#    左子树的结点个数为 i - 1 个，右子树结点的个数为 n - i 个。
#    则 f(i) = G(i-1) * G(n-i)，即组合选择。
# 代入可得 G(n) = G(0) * G(n-1) + G(1) * G(n-2) ... + G(n-1) * G(0)
# G(2) = G(0) * G(1) + G(1) * G(0)
# G(3) = G(0) * G(2) + G(1) * G(1) + G(2) * G(0)
# ...
# 每个 G 均依赖前面的 G。
# 时间复杂度：O(n^2)
class Solution:
    def numTrees(self, n: int) -> int:
        G = [0 for _ in range(n+1)]
        G[0], G[1] = 1, 1
        for i in range(2, n+1):
            for j in range(1, i+1):
                G[i] += G[j-1] * G[i-j]
        return G[n]

# Solution2: 记忆化递归（与 dp等价）
class Solution:
    def numTrees(self, n: int) -> int:
        ans = 0
        memo = dict()
        memo[0] = memo[1] = 1
        def recur(n):
            if n in memo:
                return memo[n]
            sum = 0
            for i in range(1, n+1):
                sum += recur(i-1) * recur(n-i)
            memo[n] = sum
            return sum
        return recur(n)

# Solution3: 数学 卡特兰数 https://baike.baidu.com/item/%E5%8D%A1%E7%89%B9%E5%85%B0%E6%95%B0。
# 卡特兰数满足递推式：h(n)= h(0) * h(n-1) + h(1) * h(n-2) + ... + h(n-1) * h(0) (n≥2)。
# 和上面的递推公式对应。
# 卡特兰数另类递推式：h(n+1) = h(n) * (4*n + 2) / (n + 2)。
# 递推式解为 h(n) = C(2n, n) / (n+1) = 2n * (2n-1) * ... * (n+2) * (n+1) / n! / n+1
# 可利用该递推式进行计算，注意项数的对齐。
# 时间复杂度：O(n)
class Solution:
    def numTrees(self, n: int) -> int:
        ans = 1
        j = n + 1
        for i in range(1, n+1):
            ans = (ans * j) / i
            j += 1
        ans = ans / (n + 1)
        return int(ans)

# 卡特兰数经典场景：n个元素以某种顺序入栈，有多少种出栈组合？
# 假设出栈组合设为 f(n)。
# 可以考虑将第一个元素固定在某个位置 k，k = 1, 2, ... n
# 即将长度为 n 的序列分段成两个子序列，一个为 1 ~ k-1，个数为 k-1，一个为 k+1 ~ n，个数为 n-k。
# 每一个子问题的答案即 分段成的两个序列的可能的 笛卡尔乘积。
# 序列个数为 k-1 的出栈序列种数乘以序列个数为 n-k 的出栈序列种数，
# g(k) = f(k-1) * f(n-k)
# f(n) = g(1) + g(2) + g(3) + ... g(n)
# f(n) = f(0) * f(n-1) + f(1) * f(n-2) + ... + f(n-1) * f(0)
# 即转换成卡特兰数求解。
