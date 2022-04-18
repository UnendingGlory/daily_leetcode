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

// 双指针法
// 一个指针p先走k步，再和另一个从头开始的指针q一起往前
// p到达尾部时，q即倒数第k个节点
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode *p = head, *q = head;
        for (int i = 0; i < k; ++i) {
            p = p->next;
        }
        while (p) {
            p = p->next;
            q = q->next;
        }
        return q;
    }
};
