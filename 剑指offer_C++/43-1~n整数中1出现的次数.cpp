#include "header.h"

// 输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。
// 例如，输入12，1～12这些整数中包含1的数字有1、10、11和12，1一共出现了5次。

// https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/python3si-lu-dai-ma-10fen-zhong-jiang-qi-9btr/
// 对于每一个数位，如果该位为1时1出现的次数为 前面的数字的个数 * 后面的数字的个数
// 若给定数字 3101592，某位记录为cur，前面的数字记录为a，后面的数字记录为b
// 假设某一个数位基数为base
// a = n // base // 10, b = n % base, cur = n // base % 10

// 对于百位数字5来说，base = 100, 3101 5 92，若cur = 1
// a的范围为0-3101，b的范围为0-99即base
//                有(a + 1) * base种

// 对于千位数字1来说，base = 1000, 310 1 592, cur = 1, 
// 若a的范围若为0-309，b的范围为0-999即base，有310 * base种
// 若a的为310，则b的范围为0-592，有(b + 1)种
//                a = 310，b = 592，共有 a * base + (b + 1)种

// 对于万位数字0来说，base = 10000, 31 0 1592, 若cur = 1, 
// a的范围为0-30，b的范围为0-9999即base
//                有a * base种

// 以上三种对应cur > 1，cur = 1，cur < 1的情况
// 因此从后往前遍历每一个数位即可

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