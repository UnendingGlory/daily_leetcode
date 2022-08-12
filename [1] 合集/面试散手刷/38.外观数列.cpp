#include "header.h"

// 给定一个正整数 n ，输出外观数列的第 n 项。
// 你可以将其视作是由递归公式定义的数字字符串序列：
// countAndSay(1) = "1"
// countAndSay(n) 是对 countAndSay(n-1) 的描述，然后转换成另一个数字字符串。

// 1.     1
// 2.     11
// 3.     21
// 4.     1211
// 5.     111221
// 第一项是数字 1 
// 描述前一项，这个数是 1 即 “ 一 个 1 ”，记作 "11"
// 描述前一项，这个数是 11 即 “ 二 个 1 ” ，记作 "21"
// 描述前一项，这个数是 21 即 “ 一 个 2 + 一 个 1 ” ，记作 "1211"
// 描述前一项，这个数是 1211 即 “ 一 个 1 + 一 个 2 + 二 个 1 ” ，记作 "111221"

// 要 描述 一个数字字符串，首先要将字符串分割为 最小 数量的组，每个组都由连续的最多 相同字符 组成。
// 然后对于每个组，先描述字符的数量，然后描述字符，形成一个描述组。
// 要将描述转换为数字字符串，先将每组中的字符数量用数字替换，再将所有描述组连接起来。
class Solution {
public:
    string convert(string &str) {
        char a;
        int i = 0, cnt = 1;
        string ans;
        while (i < str.size()) {
            if (i < str.size() - 1 && str[i] == str[i+1]) {
                ++cnt;
            } else {
                ans += to_string(cnt);
                ans.push_back(str[i]);
                cnt = 1;
            }
            ++i;
        }
        return ans;    
    }
    string countAndSay(int n) {
        string ans = "1";
        --n;
        while (n--) {
            ans = convert(ans);
        }
        return ans;
    }
};
