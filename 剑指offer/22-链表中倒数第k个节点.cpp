#include "ListNode.h"

// 1->2->3->4->5, k=2
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode *p = head;
        int cnt = 0;
        while (p) {
            p = p->next;
            ++cnt;
        }

        p = head;
        for (int step = 0; step < cnt - k; ++step) {
            p = p->next;
        }
        return p;
    }
};