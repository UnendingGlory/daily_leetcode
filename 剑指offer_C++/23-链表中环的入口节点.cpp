#include "header.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 快慢指针
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
      ListNode *slow = head, *fast = head;
      while (true) {
        // 如果快指针到空，则没有环
        if (fast == nullptr || fast->next == nullptr) return nullptr;
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) break;
      }

      // 假设链表有a + b个节点，a为头节点到环的步数，b为环内的步数
      // 若fast走了f步，slow走了s步
      // 则有：f = 2s; f = s + nb
      // 可推出s = nb, f = 2nb; 即两个指针走了环周长整数倍的步数
      // 如果让指针从头节点一直走，走到环的入口所用步数为a + mb
      // 而慢指针已经走了nb，只需要再走a步即可
      // 我们在头节点开一个指针，和a同步往前走，相遇处即是入口点

      fast = head;
      while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
      }
      return slow;
    }
};
