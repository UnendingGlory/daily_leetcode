#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int len = 0, cnt = 0;
        ListNode *p = head;
        while(p != nullptr) ++len, p = p->next;
        p = head;
        len = len / 2;
        while(len && p != nullptr) --len, p = p->next;
        return p;
    }
};