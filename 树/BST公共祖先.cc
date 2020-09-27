#include "binary_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:

    // 递归即可
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == p || root == q) return root;
        bool isLeft = root->val > p->val, isRight = root->val > q->val;
        // 不相等则说明p和q在当前节点两侧(利用BST性质)
        if(isLeft != isRight) return root;
        // isLeft为真则去左侧子树找
        return lowestCommonAncestor(isLeft ? root->left : root->right, p, q);
    }
};