#include <bits/stdc++.h>
using namespace std;

/** 求滑动窗口的最大值
 *  Solution1：优先级队列
 *  先把前k个值入队，然后判断堆顶元素的下标
 *  如果下标不在滑动窗口中就一直出堆顶
 *  所以为了维护下标和堆的关系，需要存pair<int, int>
 */

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> pq; // 默认大顶堆，首要是大小，次要是下标
        for (int i = 0; i < k; ++i) { // 前k个
            pq.push({nums[i], i});
        }
        vector<int> ans = {pq.top().first};
        for (int i = k; i < nums.size(); ++i) {
            pq.push({nums[i], i});
            // 如果不在窗口中则一定在前面
            while (pq.top().second <= i - k) {
                pq.pop();
            }
            ans.push_back(pq.top().first);
        }
        return ans;
    }
};

 /**
 *  在A[L...R]中，如果A[i]是最大值，则A[i]左边的元素则可以全部作废
 *  因此可以维护一个单调队列，队列头就是最大元素，每次滑动的时候更新之
 *  对窗口中的每个数，若左边有比其小的则删除之，因为在该数出队列前左边的数不可能成为最大的
 *  所以每次处理要从右端往左端处理
 *  由于每个元素最多被删除一次，因此复杂度为o(n)，达到了理论下界
 */

class MonotonicQueue {
private:
    deque<int> data;
public:
    void push(int n) {
        while (!data.empty() && data.back() < n) 
            data.pop_back();
        data.push_back(n);
    }
    
    int max() { return data.front(); }
    
    // 删除窗口之外的元素
    void pop(int n) {
        if (!data.empty() && data.front() == n)
            data.pop_front();
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MonotonicQueue window;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (i < k - 1) { //先填满窗口的前 k - 1
                window.push(nums[i]);
            } else { // 窗口向前滑动
                window.push(nums[i]);
                res.push_back(window.max());
                window.pop(nums[i - k + 1]);
            }
        }
        return res;
    }
};

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    MonotonicQueue window;
    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
        if (i < k - 1) { //先填满窗口的前 k - 1
            window.push(nums[i]);
        } else { // 窗口向前滑动
            window.push(nums[i]);
            res.push_back(window.max());
            window.pop(nums[i - k + 1]);
        }
    }
    return res;
}
