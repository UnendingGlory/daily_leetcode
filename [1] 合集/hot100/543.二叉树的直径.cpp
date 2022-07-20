#include "header.h"
// 给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。
// 比如二叉树 [1, 2, 3, 4, 5, null, null]。
// 返回3，长度为路径 [4, 2, 1, 3] 或者 [5, 2, 1, 3]

// 即求某一个结点左子树的高度 L和右子树的高度 R之和。
// 从下往上返回值，不会重复访问结点。
class Solution {
public:
    int ans;
    int getHeight(TreeNode* root) {
        if (root == nullptr) return 0;
        int l = getHeight(root->left);
        int r = getHeight(root->right);
        ans = max(ans, r + l);
        return max(l, r) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        ans = -1;
        getHeight(root);
        return ans;
    }
};



