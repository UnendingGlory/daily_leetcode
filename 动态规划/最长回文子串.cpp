#include "header.h"
using namespace std;

/** 动态规划经典问题
 *  dp[i][j]表示S[i]到S[j]是否是回文子串，1表示是，0表示否
 *  状态转移方程：dp[i][j] = dp[i + 1][j - 1], S[i] = S[j]
 *               dp[i][j] = 0, S[i] != S[j]
 *  边界条件：dp[i][i] = 1; dp[i][i + 1] = (S[i] == S[i + 1]) ? 1 : 0;
 *  那么，如何开始递推呢？由于枚举长度为L的子串时需要计算长度为L - 2的子串
 *  所以可以根据长度来递推，先计算dp长为3的，再计算4的...
 *  时间复杂度:o(n ^ 2)
 */ 

class Solution {
public:
    // 若长度为K，左端点为i，则右端点为i + K - 1
    // K 为3,4,5...直至i + K - 1超出边界
    string longestPalindrome(string s) {
        int n = s.size(), start = 0, len = 1; // 初始为1个字符
        int dp[n + 1][n + 1];
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n; ++i)
        {
            dp[i][i] = 1;
            if(i < n - 1 && s[i] == s[i + 1])
            {
                dp[i][i + 1] = 1; // 是回文子串
                start = i, len = 2;
            }
        }
        for(int K = 3; K <= n; ++K)
        {
            for(int i = 0; i + K - 1 < n; ++i) // 枚举子串起始端点
            {
                int j = i + K - 1;
                if(s[i] == s[j] && dp[i + 1][j - 1] == 1)
                {
                    // 设置变量避免重复的substr操作，substr时间复杂度为o(n)
                    start = i, len = K;
                    dp[i][j] = 1;
                }
            }
        }
        return s.substr(start, len);
    }
};