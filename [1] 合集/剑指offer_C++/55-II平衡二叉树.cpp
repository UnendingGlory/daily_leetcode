#include "header.h"


// 判断一棵树是否是平衡二叉树
// 二叉树中任意结点左右子树相差深度不超过1
// 自底向上递归，减少时间复杂度
class Solution {
public:
    // 返回值为-1即该结点不平衡
    int getHeight(TreeNode *root) {
        if (root == nullptr) return 0;
        int l_height = getHeight(root->left);
        int r_height = getHeight(root->right);
        
        if (l_height == -1 || r_height == -1 || abs(l_height - r_height) > 1) {
            return -1;
        }

        return max(l_height, r_height) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return getHeight(root) >= 0;
    }
};
