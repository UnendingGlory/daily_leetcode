#include "header.h"

// 给你一个整数 n ，对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数 ，返回一个长度为 n + 1 的数组 ans 作为答案。
// 输入：n = 5
//      [0, 1, 10, 11, 100, 101]
// 输出：[0, 1, 1, 2, 1, 2]

// Solution1: 动态规划。
// dp[n] 代表 数字n中 1的个数。
// 可以发现如下规律：
// 1. 如果 n为奇数，那么 dp[n] = dp[n-1] + 1，比如 100 -> 101。
// 2. 如果 n为偶数，那么 dp[n] = dp[n / 2]，  比如 10  -> 100。
//    因为本质上只是将 n/2 左移，在最低位补 0。
// 时间复杂度：O(n)
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n + 1);
        for (int i = 0; i <= n; ++i) {
            if (i & 1) {
                dp[i] = dp[i - 1] + 1;
            } else {
                dp[i] = dp[i / 2];
            }
        }
        return dp;
    }
};


// Solution2: 位运算算法。
// 对于任意一个整数 x，进行 x & (x - 1)操作都会使得最后一位变成0。
// 可以对于某数一直进行该操作，直到其变为0，操作的次数即该数中 1的个数。
// 时间复杂度：O(nlogn)
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n + 1);
        for (int i = 0; i <= n; ++i) {
            ans[i] = count(i);
        }
        return ans;
    }

    int count(int x) {
        int cnt = 0;
        while (x > 0) {
            x = x & (x - 1);
            ++cnt;
        }
        return cnt;
    }
};

