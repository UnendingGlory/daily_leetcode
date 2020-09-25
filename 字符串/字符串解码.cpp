#include <bits/stdc++.h>
using namespace std;

/** 可以看成词法分析器，用递归实现
 *  LL(1)文法
 */

// 递归处理
class Solution {
    string src;
    size_t p;
public:
    // 注意，数字可以不止1位，所以要多次统计
    int getDigit()
    {
        int ret = 0;
        while(p < src.size() && isdigit(src[p]))
            ret = ret * 10 + (src[p++] - '0');
        return ret;
    }

    string recur()
    {
        // 递归边界
        if(p == src.size() || src[p] == ']') return "";
        string ret;

        // 若当前字符是数字
        if(isdigit(src[p]))
        {
            int rep = getDigit();
            // 此时指针已经移动到左括号处，需要过滤左括号
            p++;
            string str = recur(); // 再次递归
            // 此时指针已经移动到右括号处，过滤右括号
            p++;
            while(rep--) ret += str; // 拼接rep次
        }
        else if(isalpha(src[p])) // 如果是字母则需拼接返回
            ret = src[p++];

        return ret + recur();
    }

    string decodeString(string s) {
        src = s, p = 0;
        return recur();
    }
};