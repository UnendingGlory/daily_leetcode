#include <bits/stdc++.h>
using namespace std;

/**
 * 方法一：暴力，枚举两个端点o(n^2)，求和o(n)
 * 方法二：求和方法可以通过前缀和预处理优化成o(n^2)
 * 方法三：(sum[i] - sum[j]) % k == 0
 *         则根据同余定理，sum[i]和sum[j]模k应该相等，所以只需要统计前缀和模K相等的次数即可
 */ 

class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        int ans = 0, n = A.size();
        unordered_map<int, int> m;
        // 为0时，自身就可以组成一个序列，不需要排列，所以m[0] = 1预处理
        m[0] = 1;
        int sum = 0;
        for(int i = 0; i < n; ++i)
        {
            sum += A[i];
            // C++取余数，负数时余数也为负数，而负数和整数应该是同模的，所以要补K
                ++m[(sum + K) % K];
        }
        // if 4, 则3 + 2 + 1，即 (n - 1) * n / 2
        for(auto i : m)
            ans += ((i.second - 1) * i.second / 2);
        return ans;
    }
};