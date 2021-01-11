#include "../header.h"
#include "ListNode.h"

// T1
// a ^ b = c
// 那么b = a ^ c
class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        vector<int> ans = {first};
        for (int i : encoded) {
            ans.push_back(ans.back() ^ i);
        }
        return ans;
    }
};

// T2
// 花里胡哨的
// 就应该先统计次数
// 交换链表的节点不用真正交换其节点，交换值即可
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        // 正数第k个
        
    }
};
// T3