#include "binary_tree.h"

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

/* 基本思路：层序遍历，每次记录一层的数量，改变指针即可
 * 小trick：新建一个temp节点用来方便修改指针
 */
class Solution {
    queue<Node *> q;
public:
    Node* connect(Node* root) 
    {
        if(root == nullptr) return nullptr;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size(); // 这一层的节点数量
            auto temp = new Node();
            for(int i = 0; i < size; ++i)
            {
                auto p = q.front();
                q.pop();
                temp->next = p;
                temp = p;
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
                // if(i == size - 1) p->next = nullptr;
            }
        }
        return root;
    }
};


/*
 * 常数时间复杂度，利用next指针
 * 用上一层处理下一层的next指针关系
 * 处理完后直接通过next指针遍历即可
 */ 

class Solution {
public:
    void handle(Node* &last, Node* &p, Node* &nextStart) 
    {
        if (last) last->next = p;
        if (!nextStart) nextStart = p;
        last = p;
    }

    Node* connect(Node* root) {
        if (!root) return nullptr;
        Node *start = root;
        while (start) 
        {
            Node *last = nullptr, *nextStart = nullptr;
            for (Node *p = start; p != nullptr; p = p->next) {
                if (p->left) {
                    handle(last, p->left, nextStart);
                }
                if (p->right) {
                    handle(last, p->right, nextStart);
                }
            }
            start = nextStart;
        }
        return root;
    }
};