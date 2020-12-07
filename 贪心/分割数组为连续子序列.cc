#include "header.h"

// LC 6598
// 判断能否将有序序列分割为连续的子序列
// 其中每个子序列的长度>=3
// 哈希 + 堆
// 哈希表中key是序列尾元素x
// data存的是堆，记录的是最短子序列的长度

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        // 最小堆
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> um;
        for (auto i : nums) {
            // 如果查找不到该i,则以i为子序列尾部元素
            // 如果找得到i - 1则将i加入序列尾部
            if (um.find(i - 1) != um.end()) {
                // 以i - 1结尾的最短的序列
                int shortLen = um[i - 1].top();
                um[i - 1].pop();
                if(um[i - 1].empty()) {
                    um.erase(i - 1);
                }
                // 以i结尾的序列长度为shortLen + 1
                um[i].push(shortLen + 1);
            }
            else { // 找不到则以i结尾的子序列长度为1
                um[i].push(1);
            }
        }
        // 遍历map，如果堆顶元素长度都>=3则可以构成
        for (const auto &i : um) {
            if(i.second.top() < 3) {
                return false;
            }
        }
        return true;
    }
};