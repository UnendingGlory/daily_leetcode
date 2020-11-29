#include "header.h"
#include "ListNode.h"
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

// 将链表list1的第a-b段删除掉
// 然后将list2插入到原来断掉的部分
// 主要就是找到list2的尾部即可

class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        vector<ListNode*> vec; // 由于有下标，所以用vector，或者顺序访问，递增记录
        ListNode *cur = list1;
        while(cur != nullptr)
        {
            vec.push_back(cur);
            cur = cur->next;
        }
        cur = list2;
        while(cur->next != nullptr)
        {
            cur = cur->next;
        }
        // cur现在指向list2的尾部
        vec[a - 1]->next = list2;
        cur->next = vec[b + 1];
        // 当然在实际中这是不正确的做法。
        // 中间一段的内存应该被释放掉，否则memory leak
        return list1;
    }
};