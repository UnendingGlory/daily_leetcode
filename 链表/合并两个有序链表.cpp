#include "header.h"
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


// 双指针法，每次选小的
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // 预设一个节点，再让指针指向这个节点
        ListNode* head = new ListNode(0), *tail = head;
        while(l1 && l2)
        {
            if(l1->val < l2->val) 
            {
                tail->next = l1;
                tail = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                tail = l2;
                l2 = l2->next;
            }
        }
        // 拼接后面的部分
        if(l1) tail->next = l1;
        if(l2) tail->next = l2;
        return head->next;
    }
};