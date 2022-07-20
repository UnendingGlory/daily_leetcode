#include "header.h"

// 给定一个非负整数数组 nums和一个整数 target。
// 向数组中的每个整数前添加 '+' 或者 '-'，然后串联所有整数，可以构成一个表达式。
// 返回通过上述方法构造的、运算结果等于 target的表达式的数目。
// 输入：nums = [1,1,1,1,1], target = 3
// 输出：5
// 解释：一共有 5种方法。
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3


// Solution1: 递归回溯，枚举所有可能性，即 2^n种可能性。
// 添加 '+' 或者 '-'，本质上只是求和时是 x还是 -x。
// 到枚举到数组尾端，如果求和 sum == target，那么 ans++。
// 时间复杂度: O(2^n)，空间复杂度：递归栈空间 O(n)
class Solution {
public:
    int ans;
    int findTargetSumWays(vector<int>& nums, int target) {
        ans = 0;
        backtrace(nums, 0, 0, target);
        return ans;
    }

    void backtrace(vector<int>& nums, int i, int sum, int target) {
        if (i == nums.size()) {
            if (sum == target) ++ans;
            return;
        }
        backtrace(nums, i + 1, sum + nums[i], target);
        backtrace(nums, i + 1, sum - nums[i], target);
    }
};

// Solution2: 动态规划。
// 该问题本质上可以转换为一个 0-1背包问题。
// 假设 sum代表所有数（不加符号）的和，P代表添加正号的数的和，N代表添加负号的数的和。
// 则有：P + N = sum; P - N = target;
// 可得：N = (sum - target) / 2;
// sum已知，target已知，即该问题转换成：
// 从 nums中选取若干个数，求使得和的结果为 (sum - target) / 2的方案的个数。
// 这样就和第 416题 [分割等和子集] 十分类似了。

// 首先做几个特判：
// 1. N肯定是一个非负数，如果 sum - target < 0，直接返回 0。
// 2. N肯定是一个整数，如果 N为奇数，直接返回 0。

// dp思路：dp[i][j]代表从数组下标 [0, i-1]中选取若干数，和为 j的方案个数。
// 分析：根据 nums[i-1]选与不选进行判断。
// 1. 若 j < nums[i-1]，那么 nums[i-1]肯定不选，dp[i][j] = dp[i-1][j]。
// 2. 若 j >= nums[i-1]，那么 nums[i-1]可选可不选，方案个数为两者的和。
//    dp[i][j] = dp[i-1][j] + dp[i - 1][j - nums[i-1]]。
// 边界条件：dp[0][0] = 1, dp[0][j] = 0
// 最终答案：dp[n][N]。
// 时间复杂度: O(n^2)，空间复杂度：O(n^2)

// 注意下标细节的处理。
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int num: nums) sum += num;
        int diff = sum - target;
        if (diff < 0 || (diff & 1)) return 0;
        int n = nums.size();
        int N = (diff >> 1);
        // dp[n][N]为答案
        vector<vector<int>> dp(n + 1, vector<int>(N + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= N; ++j) {
                if (j < nums[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        return dp[n][N];
    }
};

// Solution3: 动态规划空间优化。
// 由于 dp[i][j] 只和 dp[i-1][j]有关，因此我们可以采用滚动数组。
// 只存储一行。将空间复杂度优化为 O(n)。
// 若 j < nums[i-1]，dp[j] = dp[j]。不需要改变。
// 若 j >= nums[i-1]，dp[j] = dp[j] + dp[j - nums[i-1]]
// 由于 dp[j]需要用到上一个状态前面的值，所以需要倒序遍历。
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int num: nums) sum += num;
        int diff = sum - target;
        if (diff < 0 || (diff & 1)) return 0;
        int n = nums.size();
        int N = (diff >> 1);
        vector<int> dp(N + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = N; j >= nums[i - 1]; --j) {
                dp[j] = dp[j] + dp[j - nums[i - 1]];
            }
        }
        return dp[N];
    }
};
