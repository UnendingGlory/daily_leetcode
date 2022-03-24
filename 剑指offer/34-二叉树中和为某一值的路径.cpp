#include "header.h"
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 递归遍历，注意，题目规定要到叶子结点，所以递归边界要加以判断
class Solution {
    vector<int> tmp;
    vector<vector<int>> ans;
public:
    void recur(TreeNode* root, int remain) {
        if (root == nullptr) return;

        // 判断是否是叶子结点
        if (remain == root->val && root->left == nullptr && root->right == nullptr) {
            tmp.emplace_back(root->val);
            ans.emplace_back(tmp);
            tmp.pop_back();
            return;
        }

        tmp.emplace_back(root->val);
        if (root->left) recur(root->left, remain - root->val);
        tmp.pop_back();

        tmp.emplace_back(root->val);
        if (root->right) recur(root->right, remain - root->val);
        tmp.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int target) {
        recur(root, target);
        return ans;
    }
};