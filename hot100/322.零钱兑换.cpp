// 与第279题完全平方数思想类似（首先想到动态规划）。

// Solution1：记忆化递归。
// amount需要的硬币个数为：amount - coins[i]需要的硬币个数 + 1。
// f(amount) = min(f(amount - coins[0]), ... f(amount - coins[i])) + 1
class Solution {
public:
    vector<int> memo; // 初始化为0
    int coinChange(vector<int>& coins, int amount) {
        memo.resize(amount+1);
        return dfs(coins, amount);
    }

    // dfs代表 remain块至少需要多少硬币。
    // remain 代表剩余多少块。
    int dfs(vector<int>& coins, int remain) {
        if (remain < 0) return -1;
        if (remain == 0) return 0;
        if (memo[remain]) return memo[remain]; // 记忆化减少重复搜索

        // 寻找最小的 f
        int coins_min = INT_MAX;
        for (int coin: coins) {
            int res = dfs(coins, remain);
            if (res > 0 && res < coins_min) {
                coins_min = res + 1;
            }
        }
        
        if (coins_min == INT_MAX) {
            memo[remain] = -1; // 未找到
        } else {
            memo[remain] = coins_min;
        }
        return memo[remain];
    }
};


// Solution2: 动态规划。
// 完全背包问题。
// dp[i] 代表凑出 i所需要的最少硬币个数。
// 显然，dp[i] = min(dp[i - coins[0]], ..., dp[i - coins[n-1]]) + 1。
// 当然，需要 i - coins[j] >= 0。
// dp数组初始化：最多需要的硬币数即每次都换一块，最多为 amount个。
// 边界条件：dp[0] = 0。

// 注意，最终 dp[amount]可能超出能得到的最大的硬币个数，需要特判。
// 时间复杂度：O(n * amount)，空间复杂度：O(amount)
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int coins_max = amount + 1; 
        vector<int> dp(amount + 1, coins_max); // amount最多需要amount个硬币。
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < coins.size(); ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        if (dp[amount] > amount) { // 如果比最多需要的硬币数还多，则不存在答案
            return -1;
        }
        return dp[amount];
    }
};
