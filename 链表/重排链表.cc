#include <ListNode.h>
/**
 * L0->L1->……Ln-1->Ln重排为L0->Ln->L1->Ln-1...
 * 方法1：先存入线性表再重排
 * 方法2：先找到链表中间点，然后链表后半段就地逆置，然后归并
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if(head == nullptr) return;
        ListNode *mid = middle(head);

        // head指向头部，q指向后半段逆置后的头部
        ListNode *p = head, *q = Solution::reverse(mid->next);
        mid->next = nullptr; // 别忘了前半段最后赋值为空!

        ListNode *tempP, *tempQ;

        while(p != nullptr && q!= nullptr)
        {
            tempP = p->next;
            p->next = q;
            p = tempP;

            tempQ = q->next;
            q->next = p;
            q = tempQ;
        }
    }

    // head之后的就地逆置
    ListNode* reverse(ListNode *head)
    {
        // 别忘了prev赋值为空
        ListNode *prev = nullptr, *curr = head, *r;
        while(curr != nullptr)
        {
            r = curr->next;
            curr->next = prev;
            prev = curr;
            curr = r;
        }
        return prev;
    }

    ListNode* middle(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while(fast->next != nullptr && fast->next->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

};

