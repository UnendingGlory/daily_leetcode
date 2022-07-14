#include "header.h"
// 给定一个经过编码的字符串，返回它解码后的字符串。
// 编码规则为：k[encoded_string]
// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"
// 输入：s = "3[a2[c]]"
// 输出："accaccacc"
// 注意，s 中所有整数的取值范围为 [1, 300]。

// Solution：递归。
// 数字后必定接一个左括号，那么我们对左右括号内部进行递归，并生成对应字符串传递给外层括号。
// 对于嵌套的情况，显然需要从内层循环开始向外扩散。

// 设一个全局指针 i，用来标记在 s上的移动位置。
// 递归边界：i超出字符串长度或者 i遇到右括号时，返回 空串。
// 递归写法：如果 s[i]为数字，那么对数字进行解析，然后递归左括号内部的元素。
//         如果 s[i]为字母，那么直接加入当前递归的结果串。
// 时间复杂度：O(n)
class Solution {
public:
    string decodeString(string s) {
        int i = 0;
        return dfs(i, s);
    }

    string dfs(int &i, string s) {
        if (i == s.size() || s[i] == ']') return "";
        string ret = "";
        if (s[i] >= '0' && s[i] <= '9') {
            int cnt = parseNum(i, s);
            // 此时 i在左括号位置，越过左括号。
            i++;
            string repeat_str = dfs(i, s);
            // 此时 i在右括号位置，越过右括号。
            i++;
            while (cnt--) {
                ret += repeat_str;
            }
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            ret.push_back(s[i]);
            i++;
        }
        return ret + dfs(i, s); // 进行后续 dfs
    }

    int parseNum(int &i, string s) {
        int sum = 0;
        while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
            sum *= 10;
            sum += s[i] - '0';
            ++i;
        }
        return sum;
    }
};
