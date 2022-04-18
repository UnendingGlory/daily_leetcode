#include "header.h"
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 不带头结点的链表
// 可以借助栈或者链表就地逆转，然后模拟加法
// 带头结点的链表就地逆转算法：后面每一个元素头插法更方便 ！！，而不是尾插法！
// 要先对齐数位
class Solution {
public:
    void rev(ListNode* L)
    {
        ListNode *p = L, *q = L->next;
        L->next = nullptr; // 然后将L的后置位置空
        while(q) // q不为空时
        {
            p = L->next;
            L->next = q;
            q = p->next;
            p = q->next;
        }
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        ListNode *L1 = new ListNode(0); // 表1的头结点
        ListNode *L2 = new ListNode(0); // 表2的头结点
        L1->next = l1, L2->next = l2;

    }
};