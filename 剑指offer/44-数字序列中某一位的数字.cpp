#include "header.h"

// 数学问题，注意，题目从0开始计数
// 1-9一共有10个数字，占9位 = 1 * 9
// 10-99一共有90个数字，占2 * 90 = 180位
// 100-999一共有900个数字，占3 * 900 = 2700位
// 1000-9999一共有9000个数字，占4 * 9000 = 36000位
// digit位产生的数字占 digit * 9 * 10 ^(digit - 1) 位

// start为digit位第一个数字，count为digit位数字占的位数

// 1. 先确定n对应的数是几位数字
//    n - 9 - 180 - .... 2700 ...
// 2. 再确定剩余n所在的数字num，剩余的n都是由digit位数字贡献的
//    比如n = 6， digit = 3
//    100 101 102，那么num = 101
//    num = start + (n - 1) // digit
// 3. 确定n在数字的哪位，n在num的第(n - 1) % digit位上
//    s = to_string(num) # 转化为 string
//    res = s[(n - 1) % digit] - '0'

// 2和3其实相当于一个给定座位号和每组人数，求在第几组中的第几个

class Solution {
public:
    int findNthDigit(int n) {
        if (n == 0) return 0;
        int digit = 1, start = 1;
        long long count = 9;  // 注意count可能溢出
        while (n > count) {
            n -= count;
            digit++;          // 1, 2, 3, ...
            start *= 10;      // 10, 100, 1000, ...
            count = (long long)9 * digit * start; // 下一个digit位数字占多少位
        }
        
        int num = start + (n - 1) / digit;
        string s = to_string(num);
        int res = s[(n - 1) % digit] - '0';
        return res;
    }
};
