#include <bits/stdc++.h>
using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        if(root == nullptr) return vector<double>{};
        queue<TreeNode *> q;
        q.push(root);
        vector<double> ans;
        while(!q.empty())
        {
            int currentLevelSize = q.size();
            double sum = 0;
            for(int i = 0; i < currentLevelSize; ++i)
            {
                auto temp = q.front();
                q.pop();
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
                sum += temp->val;
               
            }
            ans.push_back(1.0 * sum / currentLevelSize);
        }
        return ans;
    }
};