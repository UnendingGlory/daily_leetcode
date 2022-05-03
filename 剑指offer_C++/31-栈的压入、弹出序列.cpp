#include "header.h"

// 第一个序列为栈的压入序列
// 判断第二个序列是否为栈的一个弹出序列

// 采用辅助栈模拟，每压入一个循环判断弹出的是否是popped的元素

class Solution {
    stack<int> s;
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        // 两个序列长度相等
        int idx = 0;
        for (int &i: pushed) {
            s.push(i);
            while (!s.empty() && popped[idx] == s.top()) {
                s.pop();
                ++idx;
            }
        }
        return s.empty();
    }
};
