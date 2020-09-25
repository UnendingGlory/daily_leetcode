#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    TreeNode *left, *right;
    int val;
};

// 递归
// 深搜
class Solution {
public:
    TreeNode* ans;
    // dfs代表是否包含该节点p或者节点q
    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        if (root == nullptr) return false;
        bool lson = dfs(root->left, p, q);
        bool rson = dfs(root->right, p, q);
        if ((lson && rson) || ((root->val == p->val || root->val == q->val) && (lson || rson))) 
        {
            ans = root;
        }
        // 返回左或右
        return lson || rson || (root->val == p->val || root->val == q->val);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        dfs(root, p, q);
        return ans;
    }
};