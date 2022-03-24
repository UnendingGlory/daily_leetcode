#include "header.h"

// 注意和最长回文子串的区别，子串必须是连续的，而子序列不一定连续
// bbbab，最长回文子串为bbb，而最长回文子序列为bbbb

// 区间dp，注意，这里返回的是长度

// 使用dp[i][j]代表S[i...j]中的最长回文子串长度，结果则为dp[0][n - 1]
// 递推公式：dp[i][j] = dp[i + 1][j - 1] + 2, S[i] == S[j]
//         dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]), S[i] != S[j]
// 边界条件: dp[i][i] = 1

// 如何递推：想要求dp[i]，需要知道dp[i+1]的信息，所以对于i需要倒着递推
//         要求dp[..][j]，需要知道dp[..][j-1]的信息，对于j要正递推

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
