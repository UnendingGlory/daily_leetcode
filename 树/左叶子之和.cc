/**
 * Definition for a binary tree node.
 */
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    int ans = 0;
public:

    void recur(TreeNode *root, int flag)
    {
        if(root == nullptr) return;
        if(root->left == nullptr && root->right == nullptr && !flag)
        {
            ans += root->val;
            return;
        }
        if(root->left) recur(root->left, 0);
        if(root->right) recur(root->right, 1);
    }

    int sumOfLeftLeaves(TreeNode* root) {
        recur(root, -1);
        return ans;
    }
};