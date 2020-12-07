#include "header.h"

/** 
 * 典型动态规划题，可以从顶部往下dp，也可以从底部向上dp
 * 在这里选择从底部向上dp的方法，较为直观
 */

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n);
        for (int i = 0; i < n; ++i)
            dp[n - 1].emplace_back(triangle[n - 1][i]);
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j)
                dp[i].emplace_back(min(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j]);
        }
        return dp[0][0];
    }
};

/**
 * 可以优化空间复杂度
 * 由于每一个dp状态只和上一个状态有关，所以o(n^2)可以优化成o(n)
 */

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(n);
        for (int i = 0; i < n; ++i) {
            dp[i] = triangle[n - 1][i];
        }
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }
        return dp[0];
    }
};