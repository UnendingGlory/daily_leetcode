#include "header.h"
using namespace std;

class MinStack {
    map<int, int> min;
    vector<int> v;
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    
    void push(int x) {
        v.push_back(x);
        min[x]++;
    }
    
    void pop() {
        if(--min[v.back()] == 0) min.erase(v.back());
        v.pop_back();
    }
    
    int top() {
        return v.back();
    }
    
    int getMin() {
        return min.begin()->first;
    }
};

// 采用辅助栈，存放当前的最小值
class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX); // 压入最大值
    }
    
    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(), x));
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{
    MinStack* obj = new MinStack();
    obj->push(3);
    obj->push(1);
    printf("%d\n", obj->getMin());
    obj->pop();
    printf("%d\n", obj->getMin());
    return 0;
}