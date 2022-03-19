#include "header.h"
using namespace std;
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
 * 链表模拟两数相加的过程
 * 先遍历两个链表得到数字，再用加法模拟
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* p = l1, *q = l2, *r;
        int C = 0;
        while(p != nullptr || q != nullptr)
        {
            int temp = 0;
            if(p == nullptr)
            {
                p = new ListNode();
                r->next = p;
                temp = q->val;
            }
            else if(q == nullptr) temp = p->val;
            else temp = p->val + q->val;
            temp += C;
            C = temp / 10;
            temp %= 10; 
            p->val = temp;
            r = p;
            if(p) p = p->next;
            if(q) q = q->next;
        }
        // 进位
        if(C) r->next = new ListNode(C);
        return l1;
    }
};
