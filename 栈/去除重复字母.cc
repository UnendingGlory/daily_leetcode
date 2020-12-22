#include "header.h"

// 去除重复字母并使得字典序最小
// bcabc -> abc
// cbacdcbc -> acdb
// 单调栈
// 由于不能重复，所以需要哈希记录
// 当栈顶的字符是最后一个的时候，栈顶就不能出栈了
// 因此需要记录出现次数

class Solution {
public:
    string removeDuplicateLetters(string s) {
        int vis[26] = {0}, num[26] = {0};
        for (char c : s) {
            ++num[c - 'a'];
        }
        string stk;
        for (char c : s) {
            // 没有访问过该字母
            if (!vis[c - 'a']) {
                while (!stk.empty() && stk.back() > c) {
                    // num还有
                    if (num[stk.back() - 'a'] > 0) {
                        vis[stk.back() - 'a'] = 0;
                        stk.pop_back();
                    } else {
                        // 没有了栈顶元素就不能出了，直接break出循环
                        break;
                    }
                }
                vis[c - 'a'] = 1;
                stk.push_back(c);
            }
            --num[c - 'a'];
        }
        return stk;
    }
};