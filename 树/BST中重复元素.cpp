#include <bits/stdc++.h>
#include "binary_tree.h"
using namespace std;

class Solution {
public:

    map<int, int> ans;

    void preorder(TreeNode *root)
    {
        if(root == nullptr) return;
        if(root->left)
        {
            if(root->val == root->left->val) ++ans[root->val];
            preorder(root->left);
        }
        if(root->right)
        {
            if(root->val == root->right->val) ++ans[root->val];
            preorder(root->right);
        }
    }

    vector<int> findMode(TreeNode* root) {
        preorder(root);
        return {};
    }
};