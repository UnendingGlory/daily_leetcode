#include "header.h"
// 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量。
// 比如 12 = 4 + 4 + 4，返回结果为 3。
// 比如 13 = 4 + 9，返回结果为 2。

// Solution1: 动态规划。
// dp[n]代表返回和为n的完全平方数的最少数量。
// 转移方程：dp[n] = min(dp[n - 1^2], dp[n - 2^2] ... dp[n - sqrt(n)^2]) + 1。
// 边界条件：dp[1] = 1
// 时间复杂度：O(n*sqrt(n))
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            int minn = INT_MAX;
            for (int j = 1; j * j <= i; ++j) {
                minn = min(minn, dp[i - j * j]);
            }
            dp[i] = minn + 1;
        }
        return dp[n];
    }
};


// Solution2: 贪心算法 + dfs。
// 本质是零钱兑换问题。
// 即给定数组coins，再给一个数n，从coins中挑选最少的coin组成n。
// 在该题中，coins数组即为 <= 自己的完全平方数。
// 贪心策略：
// 是1个数的平方和吗？是2个数的平方和吗？... 最差是n个数的平方和吗？(1+1...)

// python版本，易实现。
// class Solution:
//     def numSquares(self, n: int) -> int:
//         ps = set([i * i for i in range(1, int(n**0.5)+1)])
//         def divisible(n, count):
//             # 只有一个的话检查该数是否在 ps 数组中
//             if count == 1: return n in ps
//             # 否则 dfs 检查。
//             for p in ps:
//                 if divisible(n-p, count-1):
//                     return True
//             return False

//         for count in range(1, n+1):
//             if divisible(n, count):
//                 return count