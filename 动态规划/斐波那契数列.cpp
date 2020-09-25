#include <bits/stdc++.h>
using namespace std;

// -1代表没有计算过
class Solution {
    int dp[101];
    const int mod = 1e9 + 7;
public:
    Solution()
    {
        memset(dp, -1, sizeof(dp));
    }

    int fib(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        if(dp[n] == -1) dp[n] = fib(n - 1) + fib(n - 2);
        return dp[n] % mod;
    }
};