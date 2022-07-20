#include "header.h"

// 斐波那契数列

class Solution {
public:
    // 动态规划
    // dp[i] = dp[i - 1] + dp[i - 2]
    // 由于每一个dp值只和前面两个有关，所以可以用两个变量记录
    int numWays(int n) {
        vector<int> dp(n + 1);
        // a->dp[i - 1], b->dp[i - 2]
        // sum = 1处理n = 0的情况
        int a = 1, b = 1, sum = 1;
        for (int i = 2; i <= n; ++i) {
            sum = (a + b) % (1000000007);
            b = a;
            a = sum;
        }
        return sum;
    }
};