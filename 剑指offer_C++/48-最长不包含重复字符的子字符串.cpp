#include "header.h"


// 双指针滑动窗口题目
// 如果依次递增地枚举结果子串的起始位置，那么结果子串的结束位置也是递增的
// 若结果子串的起始位置为left，结束位置为right
// 那么选择第left + 1到right位置的字符时，显然是不重复的
// 因此可以添加第right + 1到结果子串中

// 使用左右指针
// 如果左右指针的元素重复，则左指针++
// 否则右指针++
// 最长不包含重复字符的子字符串长度即 right - left + 1
// 可以使用unordered_set
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // 哈希集合，记录每个字符是否出现过
        unordered_set<char> has;
        int n = s.size();

        // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
        int right = -1, ans = 0;

        for (int left = 0; left < n; ++left) {
            if (left != 0) {
                // 左指针向右移动一格，移除一个字符
                has.erase(s[left - 1]);
            }
            // 右指针字符不重复，就不断移动右指针
            // 右指针重复就结束，计算结果到下一层循环
            while (right + 1 < n && !has.count(s[right + 1])) {
                has.insert(s[right + 1]);
                ++right;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};