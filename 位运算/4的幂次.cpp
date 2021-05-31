#include "header.h"

// 4的幂次：最高位为1，其他位均为0，且0的个数为偶数


class Solution {
public:
    bool isPowerOfFour(int n) {
        int zero = 0;
        while(n) {
            if (n & 1 != 0) { 
                if ((n >> 1) != 0)
                    return false;
            }
            else ++zero;
            n >>= 1;
        }
        std::cout << zero;
        if (zero % 2 == 0) return true;
        return false;
    }
};