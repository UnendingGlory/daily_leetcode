#include "header.h"

// 给你一个以字符串表示的非负整数 num 和一个整数 k ，移除这个数中的 k 位数字，使得剩下的数字最小。
// 请你以字符串形式返回这个最小的数字。
// 1 <= k <= num.length <= 105。
// num 仅由若干位数字（0 - 9）组成。
// 除了 0 本身之外，num 不含任何前导零。

// Solution：贪心 + 单调栈。
// 前置知识：对于两个数 123a456 和 123b456。
// 如果 a > b，那么数字 123a456 > 123b456。
// 即数字大小取决于第一个不同的数字的大小关系。
// 若要使得剩下的数字最小，需要保证靠前的数字尽可能小。

// 考虑每一个位置的右侧相邻位置是否应该被丢弃。
// 对于位置 i，考虑 nums[i]和 nums[i+1]，大小关系。
// 如果 nums[i] > nums[i+1]，丢弃 nums[i]，可以使得得到的数更小。
// 否则保留。最多丢弃 k个数。
// 可以使用单调栈记录保留和丢弃的过程，最后栈的内容即答案。

// 特殊情况：
// 1. 丢弃的数的个数可能 < k个，应该丢弃最后几位数，即出栈。
// 2. 注意要去除前导零。
// 时间复杂度：O(n)，空间复杂度：O(n)

// 又由于元素需从队头输出，因此栈采用vector实现。
class Solution {
public:
    string removeKdigits(string num, int k) {
        vector<char> stk;
        for (char c: num) {
            while (k && !stk.empty() && stk.back() > c) {
                stk.pop_back(); // 丢弃左侧元素
                --k;
            }
            stk.push_back(c);
        }
        while (k) { // 凑齐 k个去除的数
            stk.pop_back();
            --k;
        }
        string ans;
        // 去除前缀 0
        int i = 0;
        while (i < stk.size() && stk[i] == '0') {
            ++i;
        }
        while (i < stk.size()) {
            ans.push_back(stk[i]);
            ++i;
        }
        // 如果是空，返回 "0"
        return ans == "" ? "0" : ans;
    }
};
