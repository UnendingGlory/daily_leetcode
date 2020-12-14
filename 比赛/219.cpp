#include "../header.h"

// T1
class Solution {
public:
    int numberOfMatches(int n) {
        int ans = 0;
        while (n) {
            ans += (n / 2);
            if (n != 1 && n & 1) {
                n += 1;
            }
            n /= 2;
        }
        return ans;
        // return n - 1; // n个队伍淘汰赛就需要n-1轮
    }
};

// T2
class Solution {
public:
    int minPartitions(string n) {
        int min = -1;
        for (char i : n) {
            if (i - '0' > min) {
               min = i - '0';
            }
        }
        return min;
    }
};

// T3 前缀和？
// [5,3,1,4,2]
// 错误的思路
// 目标短浅的贪心

// 石子游戏，前缀和+动态规划
// 区间dp
// dp[i][j]表示石子剩下i到j时，能取得的最大价值差
// i == j, dp[i][j] = 0，拿走后取得0
// j - i == 1, dp[i][j] = max(stones[i], stones[j])
// 拿走另一个取得最大的
// j - i > 1时，如果从左边拿，则我能获得的价值是sum[j + 1] - sum[i + 1]之和
// 和对手的差值就是sum[j + 1] - sum[i + 1] - dp[i + 1][j]，对方下一手拿
// 从右边拿，我能获得的价值是sum[j] - sum[i + 1]
// 和对手的差值就是sum[j] - sum[i + 1] -dp[i][j - 1]
// dp[i][j] = max(sum[i + 1] - sum[j] - dp[i + 1][j], sum[i] - sum[j - 1] -dp[i][j - 1])
// 最后的dp[0][n - 1]即答案，代表先手从0到n - 1能取得的最大差值
// 由于每一个位置的值需要依赖左边和下面的值，所以dp数组最好倒着计算

// [5, 3, 1, 4, 2]
// 0 5 3 7 6 
// 0 0 3 1 7 
// 0 0 0 4 2 
// 0 0 0 0 4 
// 0 0 0 0 0 


// 注意，前缀和计算，数组第一位保留0，所以要开一个n+1的数组
// 如果遍历的是原数组，那么计算num[i]到nums[j]的和
// 即sum[j + 1] - sum[i]
// 如果开n位，用sum[j] - sum[i - 1]，i = 0那会出现数组越界

class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        vector<int> sum(n + 1, 0);
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + stones[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (j - i == 1) {
                    dp[i][j] = max(stones[i], stones[j]);
                } else {
                    dp[i][j] = max(sum[j + 1] - sum[i + 1] - dp[i + 1][j], sum[j] - sum[i] - dp[i][j - 1]);
                }
            }
        }
        // for (int i = 0; i < n; ++i) {
        //     for (int j = 0; j < n; ++j) {
        //         cout << dp[i][j] << ' ';
        //     }
        //     cout << endl;
        // }
        return dp[0][n - 1];
    }
};