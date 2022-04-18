#include "header.h"

// 输入一个非负整数数组，把数组里所有数字拼接起来排成一个数。
// 打印能拼接出的所有数字中最小的一个。
// 本质上是一个排序问题。
// 排序判断规则 为：
// 若拼接字符串 xy > yx，则 x “大于” y，即x应该在y的右边
// 反之，若 xy < yx，则 x “小于” y，即x应该在y的左边
// 对于 [3,30,34,5,9]中的 3和30，3 30 < 30 3
// 所以在结果中3应该在30的右边


class Solution {
public:
    string minNumber(vector<int>& nums) {
        // 比较字典序，C++中字典序逐位比较, "30" > "3", "200" < "3"
        vector<string> str;
        for (int &i: nums) {  // 预处理加速
            str.emplace_back(to_string(i));
        }
        std::sort(str.begin(), str.end(), [](string &x, string &y) {
            return x + y < y + x;
        });
        string ans;
        for (string &i: str) {
            ans.append(i);  // append比+运算符快
        }
        return ans;
    }
};
