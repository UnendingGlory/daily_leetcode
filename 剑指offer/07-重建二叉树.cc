#include "header.h"

// 前序中序建树
// 常见题，递归
// 先序遍历先遍历到根，中序遍历中间遍历根
// 所以在每次取先序序列的第一个作为根
// 在中序中找到该位置，然后一分为二递归
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* ans = make_tree(preorder, inorder, 0, preorder.size() - 1,\
                                  0, inorder.size() - 1);
        return ans;
    }

    TreeNode* make_tree(vector<int>& preorder, vector<int>& inorder, int preL,\ 
                        int preR, int inL, int inR)
    {
        if (inL > inR) return nullptr;
        int root = preorder[preL], i;
        // 在中序序列中找根
        for (i = inL; i <= inR && inorder[i] != root; ++i);
        TreeNode *ans = new TreeNode(root);
        ans->left =  make_tree(preorder, inorder, preL + 1, preL + i - inL, inL, i - 1);
        ans->right = make_tree(preorder, inorder, preL + i - inL + 1, preR, i + 1, inR);
        return ans;
    }
};

// 肌肉记忆，一遍过，就是下标那里需要思考一下