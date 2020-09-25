#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    TreeNode *left, *right;
    int val;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // recursion build a tree
    TreeNode* create(vector<int>& preorder, vector<int>& inorder,int preL, int preR, int inL, int inR)
    {
        if(preL > preR)
        {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[preL]);
        int i;
        // find root
        for(i = inL; i <= inR; ++i)
        {
            if(inorder[i] == preorder[preL]) break;
        }
        // 到了叶子节点i是0，因此下一次preL会大于preR
        int num = i - inL;
        root->left = create(preorder, inorder, preL + 1, preL + num, inL,  i - 1);
        root->right = create(preorder, inorder, preL + num + 1, preR, i + 1,  inR);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return create(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};