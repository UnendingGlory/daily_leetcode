/*
 * 即二叉搜索树中的每个值叠加树中比其大的值
 * 应该要利用BST性质，右边和根节点均比其大
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */ 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 反序中序遍历该树，则会得到一个递减序列（利用BST的性质，打破常规树遍历的思维定势）
// 在遍历的同时每次叠加之前的和即可
class Solution {
public:
    int sum = 0;

    // 先遍历右边，再中，再左
    TreeNode* convertBST(TreeNode* root) {
        if(root != nullptr)
        {
            convertBST(root->right);
            sum += root->val;
            root->val = sum;
            convertBST(root->left);
        }
        return root;
    }
};