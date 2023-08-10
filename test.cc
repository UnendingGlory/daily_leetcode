#include "header.h"

class Solution {
public:
  void reverse(ListNode *& head) {
    ListNode *pre = nullptr, *cur = head, *nxt;
    while (cur) {
      nxt = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nxt;
    }
  }

  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *p = head;
    ListNode *dummy = new ListNode(0), *pre_tail = dummy;
    while (p) {
      ListNode *q = p;
      for (int i = 0; i < k - 1; ++i) {
        p = p->next;
      }
      ListNode *r = p->next;
      p->next = nullptr;
      reverse(q);
      pre_tail->next = p;
      pre-pre_tail = q;
      p = r;
    }
  }
};
