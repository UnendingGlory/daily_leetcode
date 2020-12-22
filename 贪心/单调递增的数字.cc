#include "header.h"

// 贪心
// 从左往右遍历，如果左边str[i - 1]比右边str[i]大
// 那么--str[i - 1]，再往左循环
// 右边统一变为9
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string str = to_string(N);
        int i = 1;
        while (i < str.size() && str[i - 1] <= str[i]) {
            ++i; 
        }
        if (i < str.size()) {
            while (i > 0 && str[i - 1] > str[i]) {
                --str[i - 1];
                --i;
            }
            // 为了保证取最大，str[i + 1...]全部改为9
            for (++i; i < str.size(); ++i) {
                str[i] = '9';
            }
        }
        return stoi(str);
    }
};