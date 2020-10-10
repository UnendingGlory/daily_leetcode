// 与I相比，II还要求求出环在链表中的起始位置
// 两种方法：一种是简单的hash表，另一种还是双指针，但是需要点技巧
#include <iostream>
#include <unordered_map>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        std::unordered_map<ListNode*, bool> m;
        while(head != nullptr)
        {
            if(m[head] == true) return head;
            // map的insert不会覆盖旧值，而是抛弃新值
            // 所以应该用下标方式
            m[head] = true;
            head = head->next;
        }
        return nullptr;
    }
};


// fast and slow pointers
// 快慢指针相遇时，再设置一个指针从头节点开始和慢指针同步走
// 最终会和慢指针在环的入口处相遇
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while(fast != nullptr)
        {
            slow = slow->next;
            if(fast->next == nullptr) return nullptr;
            fast = fast->next->next;
            // 有环
            if(fast == slow)
            {
                ListNode *ptr = head;
                while(ptr != slow)
                {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return nullptr;
    }
};