#include "header.h"

// 给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，
// 11 翻译成 “l”，……，25 翻译成 “z”。
// 一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。
// 12258
// 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"

// 经典dp题目
// 假设dp[i]为到第i位有多少种不同的翻译
// 那么若 num[i-1]和num[i]组成的数x范围在10-25，则dp[i] = dp[i-2]
// 若不在10-25，则dp[i] = dp[i - 1]

// 总结：所以如果x在10-25，则dp[i] = dp[i - 1] + dp[i - 2]
//      否则 dp[i] = dp[i - 1]
// 边界条件：dp[0] = dp[1] = 1（本来是dp[-1] = 1）
// 返回：dp[n]
class Solution {
public:
    int translateNum(int num) {
        string str = to_string(num);
        int n = str.size();
        vector<int> dp(n + 1);
        dp[0] = dp[1] = 1;
        for (int i = 1; i < n; ++i) {
            char pre = str[i - 1], cur = str[i];
            int combine = (pre - '0') * 10 + cur -'0';
            if (combine >= 10 && combine <= 25) {
                dp[i+1] = dp[i] + dp[i - 1];
            } else {
                dp[i+1] = dp[i];
            }
        }
        return dp[n];
    }
};
