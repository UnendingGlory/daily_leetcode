#include <../header.h>
#include "binary_tree.h"

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(root == nullptr) return ans;
        stack<TreeNode*> st;
        TreeNode *node = root;
        while(!st.empty() || node != nullptr)
        {
            // 将左子树全部入栈
            while (node != nullptr)
            {
                ans.emplace_back(node->val);
                st.push(node);
                node = node->left;
            }
            node = st.top();
            st.pop();
            // 出栈后直接转右子树，因为之前已经emplace back了
            node = node->right;
        }
        return ans;
    }
};
