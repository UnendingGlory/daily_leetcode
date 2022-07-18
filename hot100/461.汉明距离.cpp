#include "header.h"

// 两个整数之间的 汉明距离 指的是这两个数字对应二进制位不同的位置的数目。
// 给你两个整数 x 和 y，计算并返回它们之间的汉明距离。

// Solution1: 对两个数异或之后，求结果数中 1的数目即可。
// 转化为第 338题中的一个小问题。
// 方法1：直接对结果计数。
// 方法2：使用 z & (z - 1)，能够使得某个数最后一位 1变为 0的性质，多少次循环就是多少个1。
// 方法3：直接使用内置比特计数函数 __builtin_popcount(x)
class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x ^ y, cnt = 0;
        while (z) {
            if (z & 1) ++cnt;
            z >>= 1;
        }
        return cnt;
    }
};

class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x ^ y, cnt = 0;
        while (z) {
            z &= (z - 1);
            ++cnt;
        }
        return cnt;
    }
};

// 工程中应该直接使用内置函数。
class Solution {
public:
    int hammingDistance(int x, int y) {
        return __builtin_popcount(x ^ y);
    }
};
