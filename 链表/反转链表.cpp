#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 链表经典问题，就地反转链表。
// 带头结点头插法尾插法皆可，没有头结点的用尾插法
// 声明三个指针pre, cur, temp，修改时将cur->next指向pre即可,temp作为中间变量存储。
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // 最后一个节点是nullptr，所以第一个pre是nullptr
        ListNode *pre = nullptr, *cur = head, *temp;
        while(cur)
        {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};