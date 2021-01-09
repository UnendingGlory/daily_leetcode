#include "header.h"

// 经典快速幂
// 注意n可能为负数
// 如果n是偶数就/2
// 如果是奇数就/2

// 递归版存在函数调用且很多无效操作

class Solution {
public:

    int recur(double x, int n)
    {
        if(n == 1) return x;
        if(n & 1) return x * recur(x, n - 1);
        else return 2 * recur(x, n / 2);
    }

    double myPow(double x, int n) {
        if (n < 0) {
            n = -n;
        }
        return recur(x, n);
    }
};

// 快速幂非递归版
// 将指数的二进制位拆分，不断右移
// 如果右移后的末位是1就累乘到结果
// 比如3^10 = 3^8 * 3^2
// 由于每次指数右移了一位，相当于指数/2
// 那么底数就要翻倍弥补x = x^2

class Solution {
public:
    double myPow(double x, int n) {
        double ret = 1;
        // -2^31的相反数超出了int的范围
        long long t = (n >= 0) ? n : -static_cast<long long>(n);
        while (t) {
            if(t & 1) {
                ret *= x;
            }
            t >>= 1;
            x = x * x;
        }
        return (n >= 0) ? ret : 1.0 / ret;
    }
};

// 快速幂求余
// 有的时候x ^ a可能会溢出，超出32位甚至64位的表示范围，如何能够得到正确的余数结果
int reminder(int x, int a, int p) {
    int rem = 1;
    while (a) {
        if (a &1) {
           rem = (rem * x) % p;
        }
        a >>= 1;
        (x *= x) %= p; // 相当于x^2 % p
    }
    return rem;
}