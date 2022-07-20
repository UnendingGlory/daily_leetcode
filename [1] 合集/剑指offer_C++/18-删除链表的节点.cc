#include "../header.h"
#include "ListNode.h"

// 相比于原题有所改动
// 注意判断头节点是删除的节点
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if (head->val == val) {
            return head->next;
        }
        ListNode* p = head;
        while (p->next != nullptr && p->next->val != val) {
            p = p->next;
        }
        ListNode* q = p->next;
        p->next = q->next;
        delete q;
        return head;
    }
};

// 如果给定的不是值而是具体的节点地址
// 且保证该节点在链表中
// 如果要求O(1)内删除某节点
// 则不需要找到前置节点
// 将target的val设置成target->next的val
// 然后删除掉target->next，等价于删除target
// 这里需要考虑删除的节点是链表尾部节点的情况，即target->next == nullptr
class MySolution {
public:
    ListNode* deleteNode(ListNode* head, ListNode* target) {
        if (head == target) return nullptr; // 删除的竟是我自己

        if (target->next != nullptr) {
            target->val = target->next->val;
            ListNode* q =  target->next;
            target->next = q->next;
            delete q;
        }
        else { // 如果是链表尾部则O(n)
            ListNode *p = head;
            while (p->next != target) {
                p = p->next;
            }
            p->next = nullptr;
            delete target;
        }
        return head;
    }
};
// 当然要保证target在链表中，这将负担交给了调用者。

// 所以在链表中不一定真的需要对某个节点进行操作，只要保证最终的值结果正确即可。