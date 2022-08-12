#include "header.h"

// 给你一个整数数组 target 和一个数组 initial ，initial 数组与 target  数组有同样的维度，且一开始全部为 0 。
// 请你返回从 initial 得到  target 的最少操作次数，每次操作需遵循以下规则：
// 在 initial 中选择 任意 子数组，并将子数组中每个元素增加 1 。
// 答案保证在 32 位有符号整数以内。

// Solution1: dp
// dp[i]代表 [0...i] 子问题的操作次数。
// target[i]不超过 target[i-1]时，i-1位置拿出 target[i]次操作带上 i位置。
// target[i]超过 target[i-1]时，i-1位置拿出 target[i-1]次操作带上 i位置。
// i位置剩下的 target[i] - target[i-1]次操作只能自己做。
// 转移方程：
// dp[i] = dp[i-1], target[i] <= target[i-1]
// dp[i] = dp[i-1] + (target[i] - target[i-1]), target[i] > target[i-1]
// 边界条件：dp[0] = target[0]
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        vector<int> dp(n);
        dp[0] = target[0];
        for (int i = 1; i < n; ++i) {
            if (target[i] <= target[i - 1]) {
                dp[i] = dp[i - 1];
            } else {
                dp[i] = dp[i - 1] + target[i] - target[i - 1];
            }
        }
        return dp[n - 1];
    }
};

// Solution2: 差分数组。
// 即 dp方法空间复杂度优化。
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        int ans = target[0];
        for (int i = 1; i < n; ++i) {
            ans += max(target[i] - target[i - 1], 0);
        }
        return ans;
    }
};
