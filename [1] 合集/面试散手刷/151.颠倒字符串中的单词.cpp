#include "header.h"

// 给你一个字符串 s ，颠倒字符串中 单词 的顺序。
// 单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
// 返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
// 注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

// 输入：s = "the sky is blue"
// 输出："blue is sky the"
// 输入：s = "  hello world  "
// 输出："world hello"
// 解释：颠倒后的字符串中不能存在前导空格和尾随空格。

// 如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用 O(1) 额外空间复杂度的 原地 解法。

// Solution: 如果是非 O(1)空间复杂度，直接将分隔好的单词预存储下，然后拼接即可，O(n)。
//           如果需要 O(1)空间复杂度，那么需要思考一种就地解法。
// 1. 将整个字符串就地翻转。         "the sky is blue" -> "eulb si yks eht"
// 2. 对字符串中的每个单词再就地翻转。 "eulb si yks eht" -> "blue is sky the"
//    使用双指针进行处理即可。
// 注意细节处理即可。
class Solution {
public:
    // 翻转 s的某个子串。
    void reverseWord(string &s, int i, int j) {
        for (; i < j; ++i, --j) {
            swap(s[i], s[j]);
        }
    }
    
    string reverseWords(string s) {
        // 先对字符串进行前后空格预处理，python可以直接用 strip。
        int i = 0;
        while (i < s.size() && s[i] == ' ') {
            ++i;
        }
        int j = s.size() - 1;
        while (j >= 0 && s[j] == ' ') {
            s.pop_back();
            --j;
        }
        s = s.substr(i); // 从 i到串尾

        // 将整个字符串翻转。
        reverseWord(s, 0, s.size() - 1);
        
        // 然后将字符串按照空格分隔为单词再翻转。
        // python的字符串为不可变类型，可以直接用 split。
        string ans;
        i = 0, j = 0;
        while (j <= s.size()) {
            if (j == s.size() || s[j] == ' ') {
                reverseWord(s, i, j - 1);
                if (ans != "") { // 空格接在单词前面。
                    ans.push_back(' ');
                }
                ans += s.substr(i, j - i);
                ++j;
                // 去除单词间空格。
                while (j < s.size() && s[j] == ' ') {
                    ++j;
                }
                i = j;
            }
            ++j;
        }

        return ans;
    }
};

