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


// 优化，就地操作，不需要额外空间
// 只需要找到第a - 1个结点和第b + 1个结点即可
// 注意将要删除的结点delete掉
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode *before = list1;
        for (int i = 0; i < a - 1; ++i) {
            before = before->next;
        }
        ListNode *after = before;
        for (int i = 0; i < b - a + 2; ++i) {
            after = after->next;
        }
        ListNode *last = list2;
        while (last->next != nullptr) last = last->next;
        before->next = list2;
        last->next = after;
        // free掉删除的内存
        return list1;
    }
};


// 优化，双指针，某一个指针先走b - a + 2步，再和另外一个指针一起走a - 1步
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* p = list1, *q = list1;
        for (int i = 0; i < b - a + 2; ++i) {
            p = p->next;
        }
        for (int i = 0; i < a - 1; ++i) {
            p = p->next;
            q = q->next;
        }
        ListNode* r = list2;
        while (r->next) r = r->next;
        q->next = list2;
        r->next = p;
        return list1;
    }
};
