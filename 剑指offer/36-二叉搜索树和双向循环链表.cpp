#include "header.h"

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};


// 就地操作，中序遍历一棵二叉搜索树得到的就是有序序列
// 因此我们需要在中序遍历的同时修改二叉搜索树的指针

// 使用递归遍历保存指针，cur和pre
// cur->left = pre, pre->right = cur

// 注意，pre初始化为空，如果在递归的时候发现pre为空
// 代表走到了最左边的结点，即链表的头结点

class Solution {
    Node *pre, *head; // 链表头结点
public:
    void preorder(Node *cur) {
        if (cur == nullptr) return;

        preorder(cur->left);
        
        if (pre == nullptr) head = cur;
        else pre->right = cur;

        cur->left = pre;
        pre = cur;
        preorder(cur->right);
    }

    Node* treeToDoublyList(Node* root) {
        preorder(root);
        // 双向循环链表，所以这里需要处理下head和最后一个pre的关系
        head->left = pre;
        pre->right = head;
        return head;
    }
};


// 非递归中序：使用栈，先沿着左子树将所有的结点入栈
// 再检查出栈元素的右子树，出栈时修改指针
// 思路也是一样的
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root) return nullptr;
        stack<Node *> s;
        Node *cur = root, *pre = nullptr, *head;
        while (root || !s.empty()) {
            while (root) { // 往左遍历到底
                s.push(root);
                root = root->left;
            }

            cur = s.top();
            s.pop();

            // 中序遍历的话在这里操作
            if (pre == nullptr) head = cur;
            else pre->right = cur;
            cur->left = pre;
            pre = cur;

            root = cur->right; // 转右子树
        }
        head->left = pre;
        pre->right = head;
        return head;   
    }
};
