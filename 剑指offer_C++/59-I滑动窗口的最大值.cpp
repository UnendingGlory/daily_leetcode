#include "header.h"


// 给定一个数组和滑动窗口值k，找出所有滑动窗口里的最大值
// 输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
// 输出: [3,3,5,5,6,7] 


// Solution1: 经典优先级队列题目
// 使用STL默认优先级队列(大根堆)pq存储前一个滑动窗口的最大值
// 由于每一个滑动窗口只和前一个滑动窗口差了一个数
// 只需要判断堆顶元素下标idx和当前滑动窗口的左边界left位置关系即可
// 若idx < left, 不断将堆顶元素弹出
// pq中使用pair，记录下标和元素

// 时间复杂度：O(nlogn)，logn为调整堆的时间复杂度
// 空间复杂度：O(n)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < k; ++i) {
            q.emplace(nums[i], i);
        }
        vector<int> ans = {q.top().first};
        for (int i = k; i < n; ++i) {
            q.emplace(nums[i], i);
            while (q.top().second <= i - k) {
                q.pop();
            }
            ans.push_back(q.top().first);
        }
        return ans;
    }
};


// Solution2: 使用单调双端队列优化
// 维护一个单调队列，存储元素的下标，对应的元素从队首到队尾是递减的 (存的是下标很重要)
// 对于序列 [5, 3, 4, 1]，窗口大小为3
// 5入队，3入队： 5 3
// 由于4比3大，因此 3 出队，4入队：5 4
// 遍历到1时，由于5的下标不在滑窗中，因此5从另一侧出队

// 先预处理一遍，再遍历每一个元素num
// 先将不在滑窗中的队首元素全部pop掉或者队空
// 然后从队尾将小于num的元素全部pop掉或者队空
// 将num入队
// 再取队首的元素作为当前滑窗的最大值
// https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/solution/dong-hua-yan-shi-dan-diao-dui-lie-jian-z-unpy/

// 时间复杂度：O(n)
// 空间复杂度：O(n)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 0 || k == 0) return {};
        std::deque<int> dq; // 存储的是下标
        for (int i = 0; i < k; ++i) { // 预处理
            while(!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }

        vector<int> ans;
        ans.emplace_back(nums[dq.front()]); // 第一个滑窗
        
        for (int i = k; i < n; ++i) { // 遍历滑窗的尾端
            while(!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }
            while(!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
            ans.emplace_back(nums[dq.front()]);
        }
        return ans;
    }
};

