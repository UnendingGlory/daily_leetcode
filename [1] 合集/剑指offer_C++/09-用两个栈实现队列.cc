#include "header.h"

// 可以选择将两者操作均摊一下
// 或者选择一个操作的时间复杂度为o(1)
// append操作较多，delete操作较少，可以将append设计为o(1)
// 注意，只用在delete中倒一次即可，不用倒完再倒回去
class CQueue {
    // front and rear
    stack<int> f_stack, r_stack;    
public:
    CQueue() {
    }
    
    void appendTail(int value) {
        r_stack.push(value);
    }
    
    int deleteHead() {
        if (!f_stack.empty()) {
            int ret = f_stack.top();
            f_stack.pop();
            return ret;
        } else {
            // 如果栈f为空，将r的内容全部倒到f中
            while (!r_stack.empty()) {
                f_stack.push(r_stack.top());
                r_stack.pop();
            }
            if (!f_stack.empty())  {
                int ret = f_stack.top();
                f_stack.pop();
                return ret;
            } else {
                return -1;
            }
        }
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */