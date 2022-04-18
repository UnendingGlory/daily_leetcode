#include "header.h"

// 假设相交段长为c，两个链表只属于自己的部分长分别为a和b
// 指针p走完A链表，长度为a + c, 再走B链表
// 指针q走完B链表，长度为b + c，再走A链表
// 两指针相交时各走了a + b + c步，即相交的结点

// 注意两个链表不相交的情况，容易写出死循环
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA, *q = headB;
        // 若两个链表不相交，则p和q第二遍会指向最后一个空指针
        // 即走了a + b + 2c，空指针处相遇
        while (p != q) {
            if(p == nullptr) {
                p = headB;
            } else {
                p = p->next;
            }

            if (q == nullptr) {
                q = headA;
            } else {
                q = q->next;
            }
        }
        return p;
    }
};
