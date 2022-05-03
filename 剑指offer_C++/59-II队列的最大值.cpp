#include "header.h"


// 维护一个能求最大值的队列
// 要求max_value、push_back和pop_front的均摊时间复杂度都是O(1)。

// 维护两个队列，一个正常队列，一个为单调双端队列mq
// 正常队列操作一切如故
// 双端队列出队前需要判断队首元素是否和队列q中的队首元素相等
class MaxQueue {
    queue<int> q;
    deque<int> mq;
public:
    MaxQueue() {
    }
    
    int max_value() {
        return mq.front();
    }
    
    void push_back(int value) {
        q.push(value);
        // 注意这里要写while而不是if
        while (!mq.empty() && mq.back() <= value) {
            mq.pop_back();
        }
        mq.push_back(value);
    }
    
    int pop_front() {
        if (q.front() == mq.front()) mq.pop_front();
        int ret = q.front();
        q.pop();
        return ret;
    }
};

