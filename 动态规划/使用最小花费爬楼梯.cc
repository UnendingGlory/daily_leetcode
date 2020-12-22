#include "header.h"

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1);
        dp[0] = cost[0], dp[1] = cost[1];
        for (int i = 2; i <= n; ++i) {
            // 走一步或者走两步
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[n];
    }
};