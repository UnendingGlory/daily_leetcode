// 经典dp题
// dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + nums[i][j]
// 在原矩阵的上方和左边做padding
// 边界条件：dp[0][i] = 0, dp[j][0] = 0
// 最终结果为dp[m+1][n+1]

#include "header.h"


// O(mn), O(mn)
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]) + grid[i][j];
            }
        }
        return dp[m][n];
    }
};

// 可以优化空间复杂度
// 将二维的数组降维为一维的
// O(mn), O(n)
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        vector<int> dp(n + 1);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[j+1] = max(dp[j+1], dp[j]) + grid[i][j];
            }
        }
        return dp[n];
    }
};