#include "header.h"

// 先处理符号，再使用除基取余法
// 先得到的余数为低位
class Solution {
public:
    string convertToBase7(int num) {
        int n = num;
        string ans;
        if (num < 0) {
            n = -num;
        }
        while (n) {
            ans += (n % 7 + '0');
            n /= 7;
        }
        std::reverse(ans.begin(), ans.end());
        return num < 0 ? ans : '-' + ans;
    }
};