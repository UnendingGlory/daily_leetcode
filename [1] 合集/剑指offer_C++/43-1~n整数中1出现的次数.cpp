#include "header.h"

// 输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。
// 例如，输入12，1～12这些整数中包含1的数字有1、10、11和12，1一共出现了5次。

// https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/python3si-lu-dai-ma-10fen-zhong-jiang-qi-9btr/
// 对于每一个数位，如果该位为1时1出现的次数为 前面的数字的个数 * 后面的数字的个数
// 若给定数字 3101592，某位记录为cur，前面的数字记录为a，后面的数字记录为b
// 假设某一个数位基数为base
// a = n // base // 10, b = n % base, cur = n // base % 10

// 对于百位数字5来说，base = 100, 3101 5 92，cur = 5, cur > 1
// a的范围为0-3101，b的范围为0-99即base
//                有(a + 1) * base种

// 对于千位数字1来说，base = 1000, 310 1 592, cur = 1, 
// 若a的范围若为0-309，b的范围为0-999即base，有310 * base种
// 若a的为310，则b的范围为0-592，有(b + 1)种
//                a = 310，b = 592，共有 a * base + (b + 1)种

// 对于万位数字0来说，base = 10000, 31 0 1592, cur < 1, 
// a的范围为0-30，b的范围为0-9999即base
//                有a * base种

// 以上三种对应cur > 1，cur = 1，cur < 1的情况
// 因此从后往前遍历每一个数位即可
// 如果修改成 1-n 整数中 k出现的次数，那么分为 cur > k, cur = k, cur < k即可。

class Solution {
public:
    int countDigitOne(int n) {
        int a, b, cur;
        long long base = 1;
        int ans = 0;
        while (base <= n) { // 这里需要是等于
            a = n / base / 10;
            b = n % base;
            cur = (n / base) % 10;
            if (cur > 1) {
                ans += (a + 1) * base;
            } else if (cur == 1) {
                ans += (a * base) + (b + 1);
            } else {
                ans += a * base;
            }
            base *= 10;
        }
        return ans;
    }
};

// 题目变种：
// 计算 1-n 的整数中，数字 x出现了多少次。
// 1 <= n <= 1000000, 0 <= x <= 9。
// 思路类似，只是对于 x = 0的情况要特殊处理。
// 假设当前位为 cur，cur的基数记为 base。
// 假设 cur之前的数为 a，之后的数为 b。
// 如果 cur > x，左边数字范围: [0, a]，右边数字范围：[0, base]
//     种类数即 (a + 1) * 100 = (a + 1) * base
//     cur = x，左边数字范围: [0, a - 1]，右边数字范围: [0, base]
//                                  a, 右边数字范围：[0, b]
//     种类数即 a * base + (b + 1)
//     cur < x，左边数字范围: [0, a - 1]，右边数字范围：[0, 99]
//     种类数即 a * base
// 如果 x == 0，需要特殊处理，
// 如果 x = 0，cur之前必须要有数，即 cur > 0, 左边数字范围 [1, a]。
//                        cur = 0, 左边数字范围 [1, a - 1]。
int solution(int n, int x) {
    int base = 1, cur, a, b;
    int ans = 0;
    while (base <= n) {
        a = n / base / 10;
        cur = (n / base) % 10;
        b = n % base;
        if(x) { // x != 0的情况
            if (cur > x) {
                ans += (a + 1) * base;
            } else if (cur == x) {
                ans += a * base + (b + 1);
            } else {
                ans += a * base;
            }
        } else { // x = 0的情况要特殊处理
            if (cur > 0) {
                ans += a * base;
            } else {
                ans += (a - 1) * base + (b + 1);
            }
        }

        base *= 10;
    }
    return ans;
}
