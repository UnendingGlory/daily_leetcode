#include <bits/stdc++.h>
using namespace std;

/** 动态规划经典问题
 * 子序列可以不连续
 * dp[i]表示以下标i的数组元素为结尾的最长子序列长度
 * 则若i之前有元素A[j] < A[i]，则dp[i] = dp[j] + 1
 * 若i之前的元素均不满足，则只好自己组成一个子序列，dp[i] = 1
 * 状态转移方程:dp[i] = max(dp[j] + 1, 1); j < i && A[j] < A[i]
 * 时间复杂度:o(n^2)
 */

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int dp[n], ans = -1;
        for(int i = 0; i < n; ++i)
        {
            dp[i] = 1; // 先初始化为1，然后去遍历前面的
            for(int j = 0; j < i; ++j)
            {
                if(nums[j] < nums[i] && dp[j] + 1 > dp[i]) 
                    dp[i] = dp[j] + 1;
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};


// 寻找i之前最大的dp的操作可以用树状数组实现
// 若采用树状数组，tree[i]记录数值为i的元素出现的次数，update为o(logn)，sumRange为o(logn)
// ans就是所有sumRange的最大值 + 1
// 时间复杂度:o(nlogn)

class Solution {
public:
    vector<int> bits;
    int N;
    void add(int i, int d) {
        while (i <= N) {
            bits[i] = max(bits[i], d);
            i += i & (-i);
        }
    }
    int query(int i) {
        int res = 0;
        while (i > 0) {
            res = max(res, bits[i]);
            i -= i & (-i);
        }
        return res;
    }
    int lengthOfLIS(vector<int>& nums) {
        vector<int> s(nums.begin(), nums.end());
        sort(s.begin(), s.end());
        s.erase(unique(s.begin(), s.end()), s.end());
        N = s.size() + 1;
        bits = vector<int>(N + 1, 0);
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int k = lower_bound(s.begin(), s.end(), nums[i]) - s.begin();
            res = max(res, 1 + query(k));
            add(k + 1, query(k) + 1);
        }
        return res;
    }
};


