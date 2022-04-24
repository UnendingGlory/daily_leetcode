#include "header.h"


// 输入: "the sky is blue"
// 输出: "blue is sky the"

// 先对原字符串预处理，去头尾空格，再进行翻转，再对翻转字符串进行处理
class Solution {
public:
    void stripTail(string &s) { // 预处理尾部空格
        for (int i = s.size() - 1; i >= 0 && s[i] == ' '; --i) {
            s.pop_back(); 
        }
    }

    string reverseWords(string s) {
        stripTail(s);
        std::reverse(s.begin(), s.end());
        stripTail(s); // 相当于处理了原字符串s头部的空格
        if(s.size() == 0) return s; // 判空
        string ans, tmp;
        int pre = 0;
        for (int i = 0; i < s.size() - 1;++i) {
            if (s[i] == ' ' && s[pre] != ' ') {
                tmp = s.substr(pre, i - pre);
                std::reverse(tmp.begin(), tmp.end());
                ans.append(tmp);
                ans.push_back(' ');
                pre = i+1;
            } else if (s[i] == ' ' && s[pre] == ' ') {
                ++pre; // 连续多个空格
            }
        }
        tmp = s.substr(pre, s.size() - pre);
        std::reverse(tmp.begin(), tmp.end());
        ans.append(tmp);
        return ans;
    }
};