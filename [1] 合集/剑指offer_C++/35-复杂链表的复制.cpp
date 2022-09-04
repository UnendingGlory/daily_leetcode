#include "header.h"


class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL; // 新建结点next为空
        random = NULL;
    }
};

// 复制复杂链表
// 除了next结点之外，还有一个指向链表中随机结点的 random指针

// 难点在于复制 random指针

// Solution 1：使用 map，构建原链表到目标链表的映射。
// 遍历两遍链表，第一遍建立 原链表结点地址到目标链表对应结点地址 的映射。
// 第二遍，根据原链表的指针之间的 next和 random关系构建目标链表的映射。
// 时间复杂度 O(N),空间复杂度 O(N)。
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        unordered_map<Node *, Node *> um;
        Node *p = head;

        while (p) {
            um[p] = new Node(p->val);
            p = p->next;
        }

        p = head;
        while (p) {
            um[p]->next = um[p->next];
            um[p]->random = um[p->random];
            p = p->next;
        }
        return um[head]; // 返回头结点
    }
};


// Solution2：链表原地拼接 + 拆分
// 拼接：Node1 -> Copy1 -> Node2 -> Copy2 -> ...的形式
// 这样copy1的random就是Node1的random的next

// 要将复制完的链表一分为二，需要遍历两遍，一遍先拆分random，一遍再拆分next
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;

        Node *p = head, *q, *r;
        while (p) {
            Node *q = p;
            p = p->next;

            r = new Node(q->val);
            q->next = r;
            r->next = p;
        } // 拼接完成
        
        p = head;
        while (p) { // 先拆分random
            if (p->random) p->next->random = p->random->next;
            p = p->next->next;
        }

        p = head;
        Node *copy = head->next;
        while (p) { // 再拆分next
            q = p, r = p->next;
            p = p->next->next;
            q->next = p;
            if(p) r->next = p->next; 
        }
        return copy;
    }
};
