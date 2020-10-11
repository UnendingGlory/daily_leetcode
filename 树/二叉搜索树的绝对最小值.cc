#include <binary_tree.h>
#include <bits/stdc++.h>
using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// BST性质：中序遍历后是有序序列
// 绝对最小值肯定在相邻元素上
class Solution {
    // 赋值为__INT_MAX__
    int ans = __INT_MAX__, pre = __INT_MAX__;
public:
    void inorder(TreeNode* root)
    {
        if(root == nullptr) return;
        inorder(root->left);

        ans = min(ans, abs(pre - root->val));
        pre = root->val;

        inorder(root->right);
    }

    int getMinimumDifference(TreeNode* root) {
        inorder(root);
        return ans;
    }
};