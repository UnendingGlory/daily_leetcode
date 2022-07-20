import collections
from typing import List

# 给定滑动窗口长度，求解每个滑动窗口内元素的最大值。

# Solution1：优先级队列。
# 保持队列长度在 <= k 即可，如何保持？
# 只需要不断判断队首元素下标是否小于窗口左边界 left。
# 如果小于，那么将队首元素 pop 掉即可。
# 优先级队列，还是使用 cpp较好实现
# class Solution {
# public:
#     vector<int> maxSlidingWindow(vector<int>& nums, int k) {
#         std::priority_queue<pair<int, int>> pq; // 大根堆
#         for (int i = 0; i < k; ++i) {
#             pq.emplace(nums[i], i); // emplace方法不输入pair对，作为两个参数传入。
#         }
#         vector<int> ans = {pq.top().first};
#         // 尾端往后挪
#         for (int i = k; i < nums.size(); ++i) {
#             pq.emplace(nums[i], i);
#             while (pq.top().second <= i - k) {
#                 pq.pop();
#             }
#             ans.emplace_back(pq.top().first);
#         }
#         return ans;
#     }
# };


# Solution2: 单调队列进行优化。
# 维护一个单调队列，队列中存储元素下标。（维护的是下标，这非常重要）
# 从队首到队尾的下标对应的元素大小是严格递减的。
# 需要从队首出队，所以需要使用双端队列。
# 先预处理前k个元素，维护一个单调队列。
# 再循环后 n - k 个元素作为窗口尾端点。
# 循环中，先将下标不在窗口中的元素从队首 pop 出。
# 再维护单调队列的性质。
# 时间复杂度：O(n)，空间复杂度：O(n)
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        q = collections.deque()
        for i in range(k):
            while len(q) and nums[i] >= nums[q[-1]]:
                q.pop()
            q.append(i)
        ans = [nums[q[0]]]
        for i in range(k, len(nums)):
            while len(q) and q[0] <= i - k:
                q.popleft()
            while len(q) and nums[i] >= nums[q[-1]]:
                q.pop()
            q.append(i)
            ans.append(nums[q[0]])
        return ans
