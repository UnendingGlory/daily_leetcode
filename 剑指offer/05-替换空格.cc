#include "header.h"

// 非原地操作很简单
// 开辟一个新字符串，时间复杂度：o(n)
// 原地操作能不能时间复杂度也o(n)？
// 可以，两遍处理，第一遍先查找空格个数
// 对string resize后填充字符时从后往前填充
// 字符串常见操作
// string不需要考虑末尾反斜杠0
class Solution {
public:
    string replaceSpace(string s) {
        int blank = 0, n = s.size();
        for (char c : s) {
            if (c == ' ') {
                ++blank;
            }
        }
        // 需要替换成%20
        // 所以是size + blank*(3 - 1)
        int i = s.size() - 1;
        s.resize(n + 2 * blank);
        int j = s.size() - 1;
        while(i >= 0) {
            if (s[i] != ' ') {
                s[j--] = s[i];
            } else {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
            }
            --i;
        }
        return s;
    }
};

// python处理字符串
// class Solution:
//     def replaceSpace(self, s: str) -> str:
//         return s.replace(" ", "%20")