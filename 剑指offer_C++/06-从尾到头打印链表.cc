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

// 假设能够改变链表结构
// 则应该就地逆置
// 双指针+一个dummynode即可
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        ListNode* pre = nullptr, *cur = head, *nxt;
        while (cur != nullptr) {
            nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        vector<int> ans;
        // 现在pre是head
        while (pre != nullptr) {
            ans.push_back(pre->val);
            pre = pre->next;
        }
        return ans;
    }
};

// 假设不能改变链表结构
// 由先进后出的特点很容易想到用栈，但是这样开辟额外空间
// 改用递归进行
// 递归会有函数调用开销，而且可能函数调用栈溢出
class Solution {
    vector<int> ans;
public:
    vector<int> reversePrint(ListNode* head) {
        recur(head);
        return ans;      
    }

    void recur(ListNode *cur) {
        if (cur == nullptr) {
            return;
        } else {
            recur(cur->next);
            ans.push_back(cur->val);
        }
    }
};