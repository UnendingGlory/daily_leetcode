// 实现pow函数
// 使用快速幂方法
// 将次数n按奇数或者偶数的方法讨论
#include <bits/stdc++.h>
using namespace std;

// 递归版
class Solution {
public:
    // n可能是负数, 注意n的范围，这里要写long long,因为[-2^31]变化后是[2^31]不能用int表示
    double recur(double x, long long n)
    {
        if(n == 0) return 1;
        if(n == 1) return x;
        if(n & 1) // 奇数，这里写成x * x是为了加速运算
            return recur(x * x , n / 2) * x;
        else return recur(x * x, n / 2);
    }

    double myPow(double x, int n) {
        if(n >= 0) return recur(x, n);
        else return 1 / recur(x, -1 * (long long)n);
    }
};

// 快速幂，利用二进制思想，将幂拆成2的k次，更加高效
class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1;
        long long t = (n >= 0 ? n : -1 * (long long)n);
        while(t)
        {
            if(t & 1) ans *= x; // 末位为1，则相乘
            printf("%f\n", ans);
            t >>= 1; // 指数右移一位
            x *= x; // n右移一次相当于 n / 2，所以x要补上 * 2
        }
        return n >= 0 ? ans : 1 / ans;
    }
};
