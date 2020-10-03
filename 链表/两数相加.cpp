#include <bits/stdc++.h>
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
        ListNode* p = l1, *q = l2;
        int temp, C = 0;
        while(p != nullptr || q!= nullptr)
        {
            if(p == nullptr)
            {
                p = new ListNode();
                temp = q->val;
            }
            else if(q == nullptr) temp = p->val;
            else temp = p->val + q->val;
            temp += C;
            C = temp % 10;
            p->val = temp;
            p = p->next, q = q->next;
        }
        // 最后一位
        if(C) p->next = new ListNode(C);
        return l1;
    }
};