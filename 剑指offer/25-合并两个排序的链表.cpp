#include "header.h"
#include "ListNode.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 就地修改，每次选择最小的，不复制，预设头结点
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(0), *tail = head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                tail = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                tail = l2;
                l2 = l2->next;
            }
        }
        if (l1) tail->next = l1;
        if (l2) tail->next = l2;
        return head->next;
    }
};
