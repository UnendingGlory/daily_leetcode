#include "header.h"
// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
// 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。

// 输入: s = "cbaebabacd", p = "abc"
// 输出: [0, 6]
//       即 "cba" 和 "bac"

// Solution1: 滑动窗口。
// 统计窗口内的字符个数和模式串的字符个数是否匹配。
// 使用数组来标记个数即可。
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();
        if (sLen < pLen) return vector<int>();

        vector<int> ans, window(26), pcount(26);
        // 预处理
        for (int i = 0; i < pLen; ++i) {
            ++window[s[i] - 'a'];
            ++pcount[p[i] - 'a'];
        }
        if (window == pcount) {
            ans.emplace_back(0);
        }
        // 开始滑动，枚举尾端
        for (int i = pLen; i < sLen; ++i) {
            --window[s[i - pLen] - 'a'];
            ++window[s[i] - 'a'];

            if (window == pcount) {
                ans.emplace_back(i - pLen + 1); // 注意序号细节
            }
        }
        return ans;
    }
};

// Solution2: 滑动窗口优化。
// 上一种方法中，判断元素个数是否匹配采用数组相等的方式实现（时间复杂度高）。
// 实际上，只需要一个数组 diff 来维护滑动窗口和模式串的每个字符个数差。
// 初始化 p的字符数组然后维护数组每个元素不小于 0。
// 然后开始向右滑动窗口，减去相应字符，如果频率小于 0就收缩左边界直到频率不再小于 0。
// 当窗口长度和 p长度一致时即是答案。
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();
        if (sLen < pLen) return vector<int>();

        vector<int> ans, require(26);
        // 预处理
        for (int i = 0; i < pLen; ++i) {
            ++require[p[i] - 'a']; // 需要 p中的字符各多少个
        }
        for (int l = 0, r = 0; r < sLen; ++r) {
            --require[s[r] - 'a']; // 往右滑动即减少这种需要
            // < 0代表该字母多余，所以窗口收缩
            while (require[s[r] - 'a'] < 0) {
                ++require[s[l] - 'a'];
                ++l;
            }
            // r 位置的字母不多余，判断窗口和模式串的长度
            if (r - l + 1 == pLen) {
                ans.emplace_back(l);
            }
        }
        return ans;
    }
};
