#include "header.h"


// 思路：定义两个堆，一个小顶堆，一个大顶堆。
// 分别存储列表中上半部分的元素和下半部分的元素。
// 在求中位数的时候，如果元素个数是偶数，直接把两个堆顶元素拿出求平均。
// 如果元素个数是奇数，那么直接取元素个数多的堆的堆顶元素即可。

// 插入时，需要将大顶堆的元素先倒出，再插入小顶堆
// 思路：定义两个堆，一个小顶堆，一个大顶堆。
// 分别存储列表中上半部分的元素和下半部分的元素。
// 在求中位数的时候，如果元素个数是偶数，直接把两个堆顶元素拿出求平均。
// 如果元素个数是奇数，那么直接取元素个数多的堆的堆顶元素即可。

// 插入时，需要将大顶堆的元素先倒出，再插入小顶堆
class MedianFinder {
    std::priority_queue<int, vector<int>, less<int>> max_pq;    // 大顶堆
    std::priority_queue<int, vector<int>, greater<int>> min_pq; // 小顶堆
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        // 保证最大堆插入的元素是最小堆的最大值
        if (max_pq.size() == min_pq.size()) { 
            min_pq.push(num);
            int temp = min_pq.top();
            min_pq.pop();
            max_pq.push(temp);
        } else {
            max_pq.push(num);
            int temp = max_pq.top();
            max_pq.pop();
            min_pq.push(temp);
        }
    }
    
    double findMedian() {
        if (max_pq.size() == min_pq.size()) {
            return 1.0 * (min_pq.top() + max_pq.top()) / 2;
        } else {
            return max_pq.top();
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
