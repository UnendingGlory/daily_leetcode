#include "header.h"


// 把字符串前面的若干个字符转移到字符串的尾部。
// 输入: s = "abcdefg", k = 2
// 输出: "cdefgab"


// Solution1: 将s1和前k个截取为s2, 将s1和拼接在一起即为ss
//            取ss的[k+1, k+1+s.size)
// 时间复杂度较高
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        s.append(s.substr(0, n));
        return s.substr(n, s.size());
    }
};



// Solution2: 翻转三次
// 先对(0, k)段反转，再对(k+1, s.size)段翻转
// 再对(0, s.size)翻转
// abcdefg：ba gfedc
// ------> cdefgab
class Solution {
public:
    void reverse(string &s, int start, int end) {
        for (int l = start, r = end; l < r; ++l, --r) {
            std::swap(s[l], s[r]);
        }    
    }

    string reverseLeftWords(string s, int n) {
        this->reverse(s, 0, n - 1);
        this->reverse(s, n, s.size() - 1);
        this->reverse(s, 0, s.size() - 1);
    }
};
