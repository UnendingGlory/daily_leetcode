#include "header.h"

// 计算方案数多用dp
// dp[i][j] 表示在 i 步操作之后，指针位于下标 j 的方案数
// dp[i][j]=dp[i−1][j−1]+dp[i−1][j]+dp[i−1][j+1]

class Solution {
public:
    const int MODULO = 1000000007;

    int numWays(int steps, int arrLen) {
        int maxColumn = min(arrLen / 2, steps);  // 走太远是回不去的
        vector<vector<int>> dp(steps + 1, vector<int>(maxColumn + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= steps; i++) {
            for (int j = 0; j <= maxColumn; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j - 1 >= 0) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MODULO;
                }
                if (j + 1 <= maxColumn) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % MODULO;
                }
            }
        }
        return dp[steps][0];
    }
};

