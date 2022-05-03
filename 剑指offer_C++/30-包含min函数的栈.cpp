#include "header.h"

// 实现一个能够得到栈的最小元素的 min 函数在该栈中
// 调用 min、push 及 pop 的时间复杂度都是 O(1)


// Solution1：采用map记录最小值及其个数（map会自动排序）
// Solution2：采用辅助栈，记录最小值
class MinStack {
    stack<int> s, min_s;
public:
    /** initialize your data structure here. */
    MinStack() {
        min_s.push(INT_MAX); // 压入最大值
    }
    
    void push(int x) {
        s.push(x);
        min_s.push(std::min(min_s.top(), x)); // 每次都压入一个最小值
    }
    
    void pop() { // s和min_s大小是同步的
        s.pop();
        min_s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int min() { // 注意同名
        return min_s.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */