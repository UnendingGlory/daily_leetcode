#include "header.h"

// 即对于数组 nums，如果戳破i位置的气球，可以获得 nums[i-1] * nums[i] * nums[i+1] 的奖励。
// 如果超出数组边界，记该位置奖励为 1。
// 求能获得的最大奖励。
// 注意，每次只戳破一个气球。

// 输入：nums = [3, 1, 5, 8]
// 输出：167
// [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
// 3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

// Solution1：记忆化递归。
// f(i, j) 代表开区间 (i, j) 之间所有气球被戳破能获得的最大奖励。
// 枚举 i 和 j 区间内的每一个位置 k，假设 k是最后一个被戳爆的气球，那么
// f(i, j) = max(f(i, j) + nums[i]*nums[k]*nums[j] + f(j, k)), i <= k <= j。
// 为了防止数组越界，在数组首尾各添加一个 1。
// 递归边界：i > j, 返回 0。
// 使用记忆化二维数组减少重复计算。
// 时间复杂度: O(n^3)，空间复杂度: O(n^2)。
class Solution {
public:
    vector<int> val;
    vector<vector<int>> memo;
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        val.resize(n + 2);
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; ++i) {
            val[i] = nums[i-1];
        }
        memo.resize(n + 2, vector<int>(n + 2, -1)); // 初始化
        return dfs(0, n + 1, val);
    }

    int dfs(int i, int j, vector<int> &nums) {
        if (i > j) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int max_sum = 0;
        for (int k = i + 1; k < j; ++k) {
            int sum = nums[i] * nums[k] * nums[j];
            sum += dfs(i, k, nums) + dfs(k, j, nums);
            max_sum = max(max_sum, sum);
        }
        memo[i][j] = max_sum;
        return max_sum;
    }
};


// Solution2：动态规划。
// 区间dp。dp[i][j]代表开区间 (i, j) 之间所有气球被戳破能获得的最大奖励。
// 枚举 i 和 j 区间内的每一个位置 k，假设 k是最后一个被戳爆的气球，那么
// dp[i][j] = max(dp[i][k] + nums[i]*nums[k]*nums[j] + dp[k][j]), i <= k <= j 
// 为了防止数组越界，我们可以在首尾各添加一个 1。
// 最终答案为 dp[0][n+1]。

// 转移方程：dp[i][j] = max(dp[i][k] + nums[i]*nums[k]*nums[j] + dp[k][j]), i <= k <= j 
// 边界条件：i > j时，dp[i][j] = 0

// 注意，转移的计算需要从小区间到大区间。
// 时间复杂度：O(n^3)，空间复杂度：O(n^2)。
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n + 2, vector<int>(n + 2));
        vector<int> val(n + 2);
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; i++) {
            val[i] = nums[i - 1];
        }
        
        // 开始 dp，从小区间开始，第一个计算的是 dp[0][2]
        for (int j = 2; j < n + 2; ++j) {
            for (int i = j - 2; i >= 0; --i) {
                for (int k = i + 1; k < j; ++k) {
                    int sum = val[i] * val[k] * val[j];
                    sum += dp[i][k] + dp[k][j];
                    dp[i][j] = max(dp[i][j], sum);
                }
            }
        }
        return dp[0][n + 1];
    }
};

// 记忆化递归和动态规划一般可以相互转化且时间复杂度近似。
