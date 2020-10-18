#include <ListNode.h>


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 快慢指针，慢指针应该指向倒数第n个节点的前驱
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 哑节点
        ListNode *dummy = new ListNode(0, head);
        ListNode *first = head, *second = dummy;
        for(int i = 0; i < n; ++i) first = first->next;
        while(first)
        {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};