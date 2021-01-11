#include "../header.h"

// 常规解法
// 右移计数
// 但是得注意负数的情况会造成死循环
// 需要改进其实
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while (n) {
            if (n & 1) ++ans;
            n >>= 1;
        }
        return ans;
    }
};

// 高端解法
// 将一个整数-1，再和原整数做与运算
// 会把该整数最右边的1变成0
// 那么一个整数的二进制表示中有多少个1，
// 就可以进行多少次这样的操作
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while (n) {
            n = (n - 1) & n;
            ++ans;
        }
        return ans;
    }
};