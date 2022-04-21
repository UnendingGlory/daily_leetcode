#include "header.h"


// 一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。
// 请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

// 如果只有一个数字x出现了一次，那么可以直接通过异或运算得到该数字。
// 然后如果有两个只出现一次的数字x, y，我们需要想办法将原数组进行拆分。
// 其中一组包含x，另一组包含y。那怎么拆分呢？

// 假设a ^ a ^ b ^ b ^ c ^ c ... ^ x ^ y = z。
// 那么结果z一定不为0，所以z的二进制位一定有一位是1，假设为第n位。
// 我们根据第n位是否是1，将原数组分为两组即可。

class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int z = 0;
        for (int &i: nums) {
            z ^= i;
        }

        int m = 1; // 找到为1的某一位
        while((z & m) == 0) { // 这里需要打括号，位运算需要注意优先级
            m <<= 1;
        }

        int x = 0, y = 0;
        for (int &i: nums) { // 对原数组操作
            if (i & m) {
                x ^= i;
            } else {
                y ^= i;
            }
        }
        return vector<int> {x, y};
    }
};
