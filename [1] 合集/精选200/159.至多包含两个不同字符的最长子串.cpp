#include "header.h"

// 给定一个字符串 s，找出 至多 包含两个不同字符的最长子串 t，并返回该子串的长度。
// 输入: "eceba"
// 输出: 3
// 解释: t 是 "ece"，长度为3。

// 输入: "ccaabbb"
// 输出: 5
// 解释: t 是 "aabbb"，长度为5。

// 输入: "aaaaa"
// 输出: 5
// 解释: t 是 "aaaaa"，长度为5。

// 滑动窗口模板题，左指针和右指针。
// 如果滑窗中只有一种字符，则右指针右移。
// 如果超出两种字符，则左移左指针，直到只有两种字符，记录此时的子串长度并更新 ans。
// 注意更新哈希表。
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char, int> category;
        int ans = 0;
        for (int l = 0, r = 0; r < s.size(); ++r) {
            category[s[r]]++; // 状态更新放在前面
            while (category.size() > 2) {
                if (--category[s[l]] == 0) {
                    category.erase(s[l]);
                } 
                ++l;
            }
            ans = max(ans, r - l + 1); // 更新子串的长度
        }
        return ans;
    }
};