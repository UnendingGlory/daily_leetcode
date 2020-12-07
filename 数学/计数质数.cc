#include "header.h"

// 基本做法
// sqrt速度较慢
class Solution {
public:
    bool isPrime(int n)
    {
        for(int i = 2; i * i <= n; ++i)
        {
            if(n % i == 0)
                return false;
        }
        return true;
    }

    int countPrimes(int n) {
        int ans = 0;
        for(int i = 2; i < n; ++i)
        {
            ans += isPrime(i);
        }
        return ans;
    }
};

// 埃氏筛选法
// 如果i是素数，则i的倍数一定不是素数

class Solution {
public:
    int countPrimes(int n) {
        // 默认一开始都是素数
        vector<int> isPrime(n, 1);
        int ans = 0;
        for(int i = 2; i < n; ++i)
        {
            // i一开始肯定是素数
            if(isPrime[i])
            {
                ++ans;
                if((long long)(i * i) < n)
                // 这里可以优化成int j = i * i
                // 因为在计算i * i之前已经计算过了i*(i - 1), i*(i - 2)
                // 分别是j = i - 1和j = i - 2时计算的
                    for (int j = i + i; j < n; j += i)
                    {
                        isPrime[j] = 0;
                    }
            }
        }
        return ans;
    }
};