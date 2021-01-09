#include "../header.h"

// dp
// dp[i]代表绳子长度为i时剪成两段能达到的最大值
// 则dp[n] = max(dp[i] * dp[n - i])
// 递归边界：dp[2] = 2(自己作为整体时最大)
// dp[3] = 3（自己作为整体时最大）
// 后面的就不一定了，自己作为整体不一定比被剪完后的大
// 2 <= n <= 58
// 注意处理n == 2和n == 3时的返回值
// 分别是1和2
class Solution {
public:
    int cuttingRope(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        vector<int> dp(n + 1);
        dp[1] = 1, dp[2] = 2, dp[3] = 3;
        // 可以在1到(i- 1)的任意地方剪一刀
        for (int i = 4; i <= n; ++i) {
            for (int j = 1; j <= i - 1; ++j) {
                dp[i] = max(dp[i], dp[j] * dp[i - j]);
            }
        }
        return dp[n];
    }
};

// 引入求余问题后就不能用dp了
// 贪心 + 快速幂求余
// 尽量将绳子剪成长度为3
// 证明如下：
// 作为部分时，2不应该切分，3不应该切分
// 4切分：2 + 2 > 1 + 3
// 5切分：3 + 2
// 6切分：3 + 3（所以优先3）
// 7之后可以转换为多个短绳(1-6)，因此肯定切分比不切分乘积大
// 假设n / 3 = a
// 那么绳子以3切分完后有三种情况：
// n % 3 == 0，完美切分，返回 3^a % p
// n % 3 == 1，则将1个3拆出来成2 + 2，返回 3^(a - 1) * 4 % p
// n % 3 == 2，返回 3^a * 2 % p

class Solution {
public:

    // 快速幂求余
    int fast_remainder(int x, int a, int p) {
        long long rem = 1;
        while (a) {
            if (a & 1) {
                rem = (rem * x) % p;
            }
            a >>= 1;
            x = (long long)x * x % p;
        }
        return rem;
    }

    int cuttingRope(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        const int mod = 1e9 + 7;
        int a = n / 3, r = n % 3;
        long long ans;
        if (r == 0) {
            ans =  fast_remainder(3, a, mod) % mod;
        }
        else if (r == 1) {
            // 这里int*4也可能溢出
            ans = 4 * (long long)fast_remainder(3, a - 1, mod) % mod;
        }
        else {
            ans = 2 * (long long)fast_remainder(3, a, mod) % mod;
        }
        return ans;
    }
};