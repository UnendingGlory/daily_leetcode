#include "../header.h"
#include "ListNode.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        // 两根指针，一个指向待排，一个指向已排
        ListNode *p = head, *dummy = new ListNode(0);
        dummy->next = nullptr;
        // 一个dummy, 一个p
        while(p != nullptr)
        {
            ListNode *q = dummy, *x = p;
            p = p->next;

            for(; q->next != nullptr && q->next->val < x->val; q = q->next);
            // 则此时q->next = nullptr || q->val <= x->val
            x->next = q->next;
            q->next = x;
        }

        ListNode *ans = dummy->next;
        delete dummy; // 记得delete是必须的
        return ans;
    }
};