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
 *  Solution2：单调队列
 *  队列中的存的是下标（存值也可）
 *  队列下标的对应值是单调递减的，入队时，如果dq.back() < value
 *  则dp.pop_back()
 *  和Solution1中一样，如果队首元素不在窗口中就出队首
 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> dq;
        // 前k个先入队
        for (int i = 0; i < k; ++i) {
            while(!dq.empty() && nums[i] >= nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        // 最大值就是队首
        vector<int> ans = {nums[dq.front()]};
        for (int i = k; i < n; ++i) {
            while(!dq.empty() && nums[i] >= nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(i);
            while(dq.front() <= i - k) {
                dq.pop_front();
            }
            ans.push_back(nums[dq.front()]);
        }
        return ans;
    }
};