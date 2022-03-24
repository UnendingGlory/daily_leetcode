#include <../header.h>

// 前序非递归，使用栈
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(root == nullptr) return ans;
        stack<TreeNode *> st;
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


// 中序非递归，也使用栈，整体结构和前序是相同的，只是emplace_back的位置改变
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> s;
        while(root != nullptr || !s.empty())
        {
            while(root != nullptr)
            {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            ans.push_back(root->val);
            root = root->right;
        }
        return ans;
    }
};
