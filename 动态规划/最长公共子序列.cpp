#include <bits/stdc++.h>
using namespace std;

/** 动态规划经典问题
 * dp[i][j]表示字符串1的i号位之前和字符串2的j号位之前的LCS最长公共子序列长度
 * 若A[i] == B[j]，dp[i][j] = dp[i - 1][j - 1] + 1
 * 若A[i] != B[j]，dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
 * 边界：dp[0][j] = dp[i][0] = 0;
 * 从边界出发，最后dp[m][n]即是结果
 */

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // 之前，所以边界要 + 1
        int m = text1.size(), n = text2.size();
        int dp[m + 1][n + 1];
        for(int i = 0; i <= n; ++i) dp[0][i] = 0;
        for(int i = 0; i <= m; ++i) dp[i][0] = 0;
        for(int i = 1; i <= m; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                if(text1[i - 1] == text2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};