#include "header.h"

// 给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 
// 找出只出现一次的那两个元素。你可以按 任意顺序 返回答案。
// 和《剑指offer》 第56题相同。
// 简单方法当然是哈希表。
// 你的算法应该具有线性时间复杂度。你能否仅使用常数空间复杂度来实现？

// Solution1：采用异或运算进行分组，基于数组中只出现一次的数字的异或做法。
// a ^ a ^ d = d。
// b ^ b ^ e = e。
// a ^ a ^ b ^ b ^ c ^ c = 0。
// a ^ a ^ b ^ b ^ c ^ c ^ d ^ e = z。
// 则 z中必定有一位是 1。（100 ^ 101 = 001）
// 我们找出为 1的那一位，按照与改位的计算结果，将原数组分为两组。
// 再在两组内分别异或，即可得到结果。
// 时间复杂度：O(n)，空间复杂度：O(1)。
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int z = 0;
        for (int &i: nums) {
            z ^= i;
        }
        // 寻找 z中为 1的一位，由于 z != 0，不会死循环。
        int b = 0;
        while (((z >> b) & 1) == 0) {
            ++b;
        }
        vector<int> ans;
        int x = 0, y = 0;
        for (int &i: nums) {
            if ((i >> b) & 1) {
                x ^= i;
            } else {
                y ^= i;
            }
        }
        return {x, y};
    }
};
