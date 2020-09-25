#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 先中序遍历得到序列，再二分建树，必定是平衡二叉树
class Solution {
    vector<int> in;
public:

    void inOrder(TreeNode* root)
    {
        if(root == nullptr) return;
        inOrder(root->left);
        in.push_back(root->val);
        inOrder(root->right);
    }

    TreeNode* buildTree(int start, int end)
    {
        if(start > end) return nullptr;
        int mid = (start + end) >> 1;
        TreeNode *root = new TreeNode(in[mid]);
        root->left = buildTree(start, mid - 1); // 左边
        root->right = buildTree(mid + 1, end);
        return root;
    }

    TreeNode* balanceBST(TreeNode* root) {
        inOrder(root);
        return buildTree(0, in.size() - 1);
    }
};

int main()
{
    return 0;
}