#include "header.h"
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        q.push(root);
        int turn = 0;
        while (!q.empty()) {
            int len = q.size();
            vector<int> vec;
            for (int i = 0; i < len; ++i) {
                auto temp = q.front();
                q.pop();
                vec.push_back(temp->val);
                if (temp->left != nullptr) q.push(temp->left);
                if (temp->right != nullptr) q.push(temp->right);
            }
            if (turn & 1 == 0) {
                reverse(vec.begin(), vec.end());
            }
            ++turn;
            ans.push_back(vec);
        }
        return ans;
    }
};