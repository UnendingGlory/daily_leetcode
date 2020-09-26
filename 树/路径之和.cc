#include "binary_tree.h"

class Solution {
public:
    vector<int> path;
    vector<vector<int>> ans;
    int S;

    void inorder(TreeNode *root, int acc)
    {
        if(root == nullptr) return;
        // 叶子节点再判断避免重复
        if(root->left == nullptr && root->right == nullptr)
        {
            if(acc + root->val == S)
            {
                // 递归时一定要重置状态
                path.emplace_back(root->val);
                ans.emplace_back(path);
                path.pop_back();
            }
            return;
        }
        path.emplace_back(root->val);
        inorder(root->left, acc + root->val);
        path.pop_back();

        path.emplace_back(root->val);
        inorder(root->right, acc + root->val);
        path.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int sum)
    {
        S = sum;
        inorder(root, 0);
        return ans;
    }
};