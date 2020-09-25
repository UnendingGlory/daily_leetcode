#include <iostream>
#include <vector>
#include "binary_tree.h"
using namespace std;

class Solution {
public:

    // 在后序序列中找到中序的根节点，分为左右子树
    TreeNode *create(const vector<int>& inorder, const vector<int>& postorder,\ 
        int inl, int inr, int pl, int pr)
    {
        if(inr < inl) return NULL;
        // 后根遍历，在最后的总是根
        int temp = postorder[pr], i;
        auto root = new TreeNode(temp);
        // 在中序遍历序列中寻找根节点
        for(i = inl; i <= inr && inorder[i] != temp; ++i);

        // 由于是后根遍历
        int num = i - inl - 1; // 左子树节点个数
        root->left = create(inorder, postorder, inl, i - 1, pl, pl + num - 1); 
        root->right = create(inorder, postorder, i + 1, inr, pl + num, pr - 1);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        auto ans = create(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
        return ans;
    }
};