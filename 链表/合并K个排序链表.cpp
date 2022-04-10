#include "header.h"
using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};
// 可以将两两合并链表，然后再总体合并

// k指针法，一次选一个，优先级队列，判队空即可，不需要拼接操作
class Solution {
public:
    // 在struct里自定义了优先级，在优先级队列中便不需要重新定义
    // 优先级队列的大小关系是反的
    
    // 要记录值和指针
    struct Headnode {
        int val;
        ListNode *ptr;
        bool operator < (const Headnode &rhs) const {
            return val > rhs.val;
        }
    };

    priority_queue <Headnode> q;

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        for (auto node: lists) {
            if (node) q.push({node->val, node});
        }
        ListNode head(0), *tail = &head;
        while (!q.empty()) {
            auto f = q.top(); q.pop();
            tail->next = f.ptr; 
            tail = tail->next;
            if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
        }
        return head.next;
    }
};
