#include "header.h"

// 维护一个大小为k的大顶堆
// 如果元素个数小于k，则全部入堆
// 否则，比较num和堆顶元素x大小，如果num >= x则跳过
// 如果num < x则入堆

class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        std::priority_queue<int, vector<int>> pq;
        for (int &num: arr) {
            if (pq.size() < k) {
                pq.push(num);
            } else {
                if (num < pq.top()) {
                    pq.pop();
                    pq.push(num);
                }
            }
        }
        vector<int> ans;
        while (!pq.empty()) {
            ans.emplace_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};
