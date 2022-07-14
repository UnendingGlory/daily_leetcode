#include "header.h"

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        std::priority_queue<pair<int, int>> pq; // 大根堆
        for (int i = 0; i < k; ++i) {
            pq.emplace(nums[i], i);
        }
        vector<int> ans = {pq.top().first};
        // 尾端往后挪
        for (int i = k; i < nums.size(); ++i) {
            pq.emplace(nums[i], i);
            while (pq.top().second <= i - k) {
                pq.pop();
            }
            ans.emplace_back(pq.top().first);
        }
        return ans;
    }
};

int main() {
    std::cout << std::hash<string> h("aaa") << std::endl;
    return 0;
}