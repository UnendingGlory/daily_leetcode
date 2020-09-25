#include <bits/stdc++.h>
using namespace std;

// 核心思想：将所有元素分为两组，相同的在一组，不同的在另一组，然后直接做异或
// 大致思路：先对所有元素进行异或得到结果
// 再根据异或结果中有1的位再对所有元素进行异或，
// 对所有元素进行分组，元素不同，所以肯定会有一位为1

class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        // 存储异或结果
        int res = 0;
        for(int i : nums) res ^= i;
        int k = 1;
        // 左移去找异或结果中最低位的1
        while((k & res) == 0) k <= 1;
        int a = 0, b = 0; // 分成两组，记录结果
        for(int i : nums)
        {
            if(k & i) // 按位与
                a ^= i;
            else b ^= i;
        }
        return vector<int>{a, b};
    }
};