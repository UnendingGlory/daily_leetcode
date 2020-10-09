#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 判断链表中是否有环
// 经典快慢指针法
// 如果有环，则两指针必定在某一个位置上相遇（在环上）
// 如果没有环，则快指针会最先走到末尾
// myVersion
class Solution {
public:
    bool hasCycle(ListNode *head) 
    {
        if(head == nullptr) return false;
        ListNode *fast = head->next, *slow = head;
        // 判断快指针
        while(fast != nullptr && fast->next != nullptr)
        {
            if(fast == slow) return true;
            fast = fast->next->next;
            slow = slow->next;
        }
        return false;
    }
};

// 官方循环写法
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == NULL) return false;
        // fast赋值为head->next
        auto slow = head, fast = head->next;
        // 判断是否有环
        while(slow != fast)
        {
            // fast走到顶说明没有环
            if(fast == NULL || fast->next == NULL) return false;
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
