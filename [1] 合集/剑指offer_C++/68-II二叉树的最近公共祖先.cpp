#include "header.h"

// 注意所有结点的值需要是唯一的，才能保证有单一解
// 二叉树的LCA
// 二叉树的值就没有规律了
//       A
//     B   C
//    D E F G

// D 和 F 的 LCA 为A
// D 和 E 的 LCA 为B
// B 和 E 的 LCA 为B

// Solution: 递归
// 若root是 p和q 的LCA，只可能是以下几种情况之一
// 1. p 和 q分属 root的 两侧 （即左、右子树中）
// 2. p = root, q在root的左或者右子树中
// 3. q = root, p在root的左或者右子树中
// 考虑通过递归对二叉树进行先序遍历，当遇到节点 p 或 q 时返回。
// 从上到下递归，从底至顶回溯，
// 当节点 p, q 在节点 root 的异侧时，节点 root 即为最近公共祖先
// 则向上返回 root 。

// 递归写法：
// 当root穿过叶结点，直接返回nullptr
// 若root = p 或者 root = q， 返回 root
// 使用left 和 right 记录root的左侧和右侧返回
// 1. 若left和right同时为空，返回空
// 2. 若left和right同时不为空，即p和q在root两侧，返回root
// 3. 若left为空，right不为空，有两种情况
//    * p和q的其中一个在root右子树中，另一个指向 right
//    * p和q的两个都在root右子树中，此时right为 p 和 q 的 LCA
//    综合起来，若left为空，right不为空，直接返回right
// 4. 若right为空，left不为空，返回left
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        // 以下写法合并了4种情况
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        return root;
    }
};

// TODO: 后序遍历非递归版。
// Solution1: 可以遍历两遍树生成两个链表，找到两个链表的第一个公共结点即可（68-III题中有实现）。
// Solution2: 基于非递归版后序遍历。见目录： 树/非递归遍历.cpp。
//            存储可能的最近公共祖先，后序遍历时，将 p和 q的父结点向上层传递即可。    
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return nullptr;
        }
        stack<TreeNode *> s;
        TreeNode *pre = nullptr, *cur = root;
        while (cur != nullptr || !s.empty()) {
            // 找到最左侧子结点
            while (cur != nullptr) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            // 如果该结点可以访问
            if (cur->right == nullptr || cur->right == pre) {
                // 可以访问时，再将 p和 q的父结点向上层传递。
                if (cur->left == p || cur->right == p) {
                    p = cur;
                }
                if (cur->left == q || cur->right == q) {
                    q = cur;
                }
                if (p == cur && q == cur) {
                    return cur;
                }
                pre = cur;
                cur = nullptr; // 防止左子节点重复循环
            } else {
                s.push(cur); // 该结点不能访问，打回栈中
                cur = cur->right; // 转右节点
            }
        }
        return nullptr;
    }
};


class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> stk;
        if (root) stk.push(root);
        while (!stk.empty()) {
            root = stk.top(); stk.pop();
            if (root) {
                stk.push(root);
                stk.push(nullptr);
                if (root->right) stk.push(root->right);
                if (root->left) stk.push(root->left);
            } else {
                root = stk.top(); stk.pop();
                if ((root->left == p && root->right == q) ||
                    (root->left == q && root->right == p)) return root;
                if (root == p && (root->left == q || root->right == q)) return root;
                if (root == q && (root->left == p || root->right == p)) return root;
                if (root->left == p || root->right == p) p = root; // 更新 p到上层
                if (root->left == q || root->right == q) q = root; // 更新 q到上层
            }
        }
        return nullptr;
    }
};
