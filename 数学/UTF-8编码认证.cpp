#include "../header.h"

// 对于1字节的字符，第一位设为0
// 第一个字节的前n位如果为1，则表示它是一个n位的UTF-8编码

// 后面位数的前两位应该为10

// Solution 1：直接模拟
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int n = data.size();
        for (int i = 0; i < data.size(); ) {
            int t = data[i], j = 7;
            while (j >= 0 && (((t >> j) & 1) == 1)) --j; // 位运算加括号
            int cnt = 7 - j; // 开头有几个1
            if (cnt == 1 || cnt > 4) return false;
            if (i + cnt > n) return false; // 末尾不够
            for (int k = 1; k < cnt; ++k) {
                t = data[i + k];
                if (((t >> 7) & 1) == 1 && ((t >> 6) & 1) == 0) {
                    continue;
                }
                return false;
            }
            if (cnt == 0) ++i; // 0开头
            else i += cnt;
        }
        return true;
    }
};


// Solution 2: 找规律位运算
class Solution1 {
public:
    bool validUtf8(vector<int>& data) {
        int n = data.size(), cnt = 0; // cnt代表往后寻找几位
        for (int i = 0; i < n; ++i) {
            int t = data[i];
            if (cnt) {
                if ((t & 0x80) != 0x80) return false;
                --cnt;
                continue;
            }
            
            if ((t & 0xF8) == 0xF0) { // n + 1位要为0
                cnt = 3;
            } else if ((t & 0xE0) == 0xE0) {
                cnt = 2;
            } else if ((t & 0xC0) == 0xC0) {
                cnt = 1;
            } else if ((t & 0x80) == 0x80) { // cnt == 0的情况
                return false;
            }
        }
        return cnt == 0;
    }
};


int main() {
    Solution1 s;
    vector<int> data {145};
    s.validUtf8(data);
    return 0;
}
