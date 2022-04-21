#include "header.h"


// 求二叉树的深度，经典递归
class Solution {
public:
    int dfs(TreeNode* root) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) { // 叶结点
            return 1;
        }
        int d = max(dfs(root->left), dfs(root->right));
        return d + 1;
    }

    int maxDepth(TreeNode* root) {
        return dfs(root);
    }
};


// 简化
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
