#include "header.h"

// 给定一个罗马数字，将其转换成整数。
// 输入：s = "III"
// 输出：3

// 输入：s = "IV"
// 输出：4

// 输入: s = "MCMXCIV"
// 输出: 1994
// 解释: M = 1000, CM = 900, XC = 90, IV = 4.

// 字母表：I 1; V 5; X 10; L 50; C 100; D 500; M 1000
// 通常情况下，罗马数字中小的数字在大的数字的右边。
// 特殊情况：
// 1. I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
// 2. X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
// 3. C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。

// Solution：模拟
// 
class Solution {
private: 
    unordered_map<char, int> hashtable = { // cpp 哈希表初始化
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
public:
    int romanToInt(string s) {
        int n = s.size(), ans = 0;
        for (int i = 0; i < s.size(); ++i) {
            int value = hashtable[s[i]];
            if (i < n - 1 && value < hashtable[s[i + 1]]) {
                ans -= value;
            } else {
                ans += value;
            }
        }
        return ans;
    }
};
