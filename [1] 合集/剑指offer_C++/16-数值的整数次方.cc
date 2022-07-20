#include "header.h"

// 非递归快速幂问题
// 注意处理溢出和指数为负数的情况
// 这里是double，64位
class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1;
        // 整数中-n的情况可能溢出！🤮
        // [-2^31, 2^31 - 1]
        long long newn = n < 0 ? -(long long)n : n;
        while (newn) {
            if (newn & 1) ans *= x;
            newn >>= 1;
            x *= x;
        }
        return n < 0 ? 1 / ans : ans;
    }
};