#include "header.h"

// 给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。
// 返回被除数 dividend 除以除数 divisor 得到的商。
// 整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

// 1. 被除数和除数均为 32位有符号整数且只能使用 32位整数。
// 2. 除数不为 0。
// 3. 假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31,  2^31 − 1]。本题中，如果除法结果溢出，则返回 2^31 − 1。
//    即不能使用 long类型。

// Solution1: 辗转相除法。
// 以 22 / 3 = 7 ... 1 为例。
// 22 - 3 = 19 >= 3
// 19 - 3 = 16 >= 3
// ...
// 4 - 3 = 1 >= 3
// 1 - 3 = -2 <= 3
// 统计减去 3的次数即可。
// 预处理：对于除数和被除数均同号的情况下该思路可行，且结果为正。
//        异号的情况下需要将两数转换为同号。
//        int32 范围是 [-2^31, 2^31 - 1]
// 如果均转换为正数，那么 -2^31要变成 2^31，会溢出。
// 因此均转换为负数即可。 
// 注意处理边界情况：
// 如果 -2^31 / -1，那么结果会溢出，需要返回 2^31 - 1。

// 时间复杂度：O(n)，会超时
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        int sign = ((dividend > 0) ^ (divisor > 0));
        if (dividend > 0) {
            dividend = -dividend;
        }
        if (divisor > 0) {
            divisor = -divisor;
        }
        int ans = 0;
        while (dividend <= divisor) {
            ++ans;
            dividend -= divisor;
        }
        return sign ? -ans : ans; // 不能用乘号
    }
};

// Solution2: 类二分查找。
// 由于不能使用乘法，因此可以运用位运算，以 2的倍数，扩大被减数的范围。
// 注意，上面转换中将两个数均转换为负数，而在 C/C++中，不支持对负数进行位运算。
// 也可使用位运算，只需要像 Solution 3中对除数和被除数为负数最大值情况进行分类讨论即可。
// 所以只能用加法实现倍数的扩大，记每一轮倍数为 k。
// 轮次1：a = 22, b = 3, k = 1
// 22 - (3 + 3) = 22 - 6 = 16 > 0, k = 1 + 1 = 2
// 22 - (6 + 6) = 22 - 12 = 10 > 0，k = 2 + 2 = 4
// 22 - (12 + 12) = 22 - 24 = -2 < 0

// 轮次2：a = 10, b = 3, k = 1
// 10 - (3 + 3) = 10 - 6 = 4 > 0，k = 1 + 1 = 2
// 10 - (6 + 6) = 10 - 12 = -2 < 0

// 轮次3：a = 4, b = 3, k = 1
// 4 - (3 + 3) = 4 - 6 = -2 < 0

// 轮次4：a = 1, b = 3, 结束循环
// 最终结果为各轮次的倍数相加。
// 即 4 + 2 + 1 = 7
// 时间复杂度: 每一轮中时间复杂度为 O(logn)，共有 O(logn)轮
// 总时间复杂度为 O(logn) * O(logn)
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        int sign = ((dividend > 0) ^ (divisor > 0));
        if (dividend > 0) {
            dividend = -dividend;
        }
        if (divisor > 0) {
            divisor = -divisor;
        }
        int ans = 0;
        while (dividend <= divisor) {
            int b = divisor;
            int k = 1; // 倍数计数
            // b + b可能溢出，因此需要判断
            // 0x1100... = 0xc0000000
            while (b >= 0xc0000000 && dividend <= b + b) {
                b += b;
                // k + k也可能溢出，溢出返回 INT_MAX
                if (k > INT_MAX / 2) {
                    return INT_MAX;
                }
                k += k;
            }
            dividend -= b;
            ans += k;
        }
        return sign ? -ans : ans; // 不能用乘号
    }
};

// Solution3：位运算。
// 每次从整数位最大位数开始尝试，除数左移31位、30位、... 0位

// 在 C/C++中，不支持对负数进行位运算。
// 所以需要均转成正数，并对 -2^31 溢出情况进行特判。
// 轮次1：a = 22, b = 3
// 22 - (3 << 31) < 0
// 22 - (3 << 30) < 0
// ...
// 22 - (3 << 3) = 22 - 24 = -2 < 0
// 22 - (3 << 2) = 22 - 3 * 4 = 10 > 0，k = 1 << 2 = 4

// 10需要重新过一遍轮次1吗？不需要。
// 只需要继续往下左移即可。
// 10 - (3 << 1) = 10 - 3 * 2 = 4 > 0, k = 1 << 1 = 2
// 4 - (3 << 0) = 1 > 0,               k = 1 << 0 = 1
// 到达了0，结束循环。

// 时间复杂度：O(32) = O(1)
class Solution {
public:
    int divide(int a, int b) {
        if (a == INT_MIN && b == -1) return INT_MAX;

        int res = 0;

        // 针对除数和被除数，处理边界，防止转正数溢出
        // 除数如果绝对值最大，结果必为 0 或 1
        if (b == INT_MIN) {
            return a == b? 1 : 0;
        }

        // 被除数如果绝对值最大，先减去一个除数
        if (a == INT_MIN) {
            a -= -abs(b);
            res += 1;
        }

        int sign = (a > 0) ^ (b > 0) ? -1 : 1;

        int ua = abs(a);
        int ub = abs(b);
        for (int i = 31; i >= 0; i--) {
            if ((ua >> i) >= ub) {
                ua = ua - (ub << i);
                // 代码优化：这里控制 ans 大于等于 INT_MAX
                if (res > INT_MAX - (1 << i)) {
                    return INT_MIN;
                }
                res += (1 << i);
            }
        }
        // bug 修复：因为不能使用乘号，所以将乘号换成三目运算符
        return sign == 1 ? res : -res;
    }
};