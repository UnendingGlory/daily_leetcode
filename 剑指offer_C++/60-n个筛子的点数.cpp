#include "header.h"


// 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。
// 输入n，打印出s的所有可能的值出现的概率。

// 你需要用一个浮点数数组返回答案。
// 其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。


// Solution1：暴力思路
// 每个骰子可以摇到1到6，共有 6^n 种可能性。
// n个骰子，摇到的范围为[n, 6n]，共有6n - n + 1 = 5n + 1种可能。
// 遍历每一个骰子，统计点数和sum，sum对应的次数++。
// 对所有的sum除以 6^n 即可得到最终结果。
// 时间复杂度O(6^n)
// n = 11时，必定会超时

// Solution2：动态规划
// 假设输入n个骰子的概率为 f(n)，点数和为x的概率为 f(n, x)
// 当添加的骰子点数为1时，前n-1个骰子的点数和应为x - 1
// 当添加的骰子点数为2时，前n-1个骰子的点数和应为x - 2
// ...
// 当添加的骰子点数为6时，前n-1个骰子的点数和应为x - 6
// 递推公式：f(n, x) = 1/6[f(n-1, x-1) + f(n-1,x-2) + ... f(n-1, x-6)]
// 边界条件：f(1, 1) = f(1, 2) = ... = f(1, 6) = 1/6

// 注意处理 x-i 的越界问题，因为 x-i 可能 <= 0，这是没有意义的
// 时间复杂度：O(6*n^2)，即O(n^2)，空间复杂度O(n^2)

// 空间复杂度可以优化，第i行只和第i-1行有关，空间可以优化成O(n)
class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<double> ans(5*n + 1); // 结果的可能性有5n + 1种
        vector<vector<double>> dp(n+1, vector<double>(6*n)); // 点数和范围是[n, 6n]
        for (int i = 1; i <= 6; ++i) dp[1][i] = 1.0 / 6;
        for (int i = 2; i <= n; ++i) {
            for (int j = i; j <= 6*i; ++j) {
                for (int k = 1; k <= 6; ++k) {
                    if (j - k <= 0) break; // 后面的都小于0
                    dp[i][j] += (dp[i-1][j-k] / 6.0);
                }
            }
        }
        for (int i = n; i <= 6*n; ++i) {
            ans.emplace_back(dp[n][i]);
        }
        return ans;
    }
};

// Solution3：动态规划优化
// 由逆推改为正推，同时降低空间复杂度
// f(n, x) 对于 f(n+1, x+1), f(n+1, x+2)... f(n+1, x+6)的贡献均是1/6
// 时间复杂度: O(n^2)，空间复杂度：O(n)
class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<double> dp(6, 1.0 / 6); // 初始只有1个骰子的时候均是1/6
        for (int i = 2; i <= n; ++i) {
            vector<double> tmp(5 * i + 1, 0); // i个骰子的时候有5i + 1种可能
            for (int j = 0; j < dp.size(); ++j) { // dp是上一个n时
                for (int k = 0; k < 6; ++k) {
                    tmp[j + k] += dp[j] / 6.0;
                }
            }
            dp = tmp;
        }
        return dp;
    }
};
