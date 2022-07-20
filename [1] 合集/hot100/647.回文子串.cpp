#include "header.h"

// 给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。
// 输入：s = "aaa"
// 输出：6
// 解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"
// 即第5题，最长回文子串的一个拓展。
// 在第5题求解最长回文子串的过程中维护一个变量计数即可。

// Solution1: dp动态规划
// dp[i][j]代表字符串 i到 j是否为回文子串。
// 1. 若 s[i] == s[j], dp[i][j] = dp[i-1][j-1]
// 2. 若 s[i] != s[j], dp[i][j] = False
// 边界条件：dp[i][i] = True
//         dp[i][i+1] = True if s[i] == s[i+1] else False
// 递推：已知长度为 1和 2的子串的 dp值。
//      依次递推长度为 3, 4 ..... n 的子串。
// 时间复杂度：O(n^2)，空间复杂度：O(n^2)
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int ans = n; // 长度为1的子串
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
            if (i < n - 1 && s[i] == s[i + 1]) {
                ++ans;
                dp[i][i + 1] = true; 
            }
        }
        // 枚举 3 .. n 的子串
        for (int k = 3; k <= n; ++k) {
            for (int i = 0; i <= n - k; ++i) { // 枚举子串的起点
                int j = i + k - 1; // 子串终点
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    ++ans;
                    dp[i][j] = true;
                }
            }
        }
        return ans;
    }
};


// Solution2: 中心扩展法。
// 从某个字符作为中心点，双指针往两边进行扩展，检查字符是否相等即可。
// 注意，需要对 "a" 和 "aa" 这种情况分别处理。
// 即对奇数和偶数回文子串分开处理。
// 时间复杂度：O(n^2)
class Solution {
public:
    int ans = 0;
    void expandCenter(string s, int i, int j) {
        for (; i >= 0 && j < s.size() && s[i] == s[j]; --i, ++j) {
            ++ans;
        }
    }

    int countSubstrings(string s) {
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            expandCenter(s, i, i);
            if (i < n - 1 && s[i] == s[i + 1]) {
                expandCenter(s, i, i + 1);
            }
        }
        return ans;
    }
};


// Solution3: Manacher 马拉车算法，处理字符串，优化中心扩展法。
// 时间复杂度为 O(n)。
// TODO：较复杂，有空详解。
