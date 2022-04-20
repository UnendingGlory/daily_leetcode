#include "header.h"


// 二叉搜索树的中序遍历为递增序列
// 逆序中序遍历为递减序列(右中左)
// 第k个大的节点即逆序遍历的第k个节点
class Solution {
    int k, ans;
public:
    void revPreOrder(TreeNode* root) {
        if(root == nullptr) return;
        revPreOrder(root->right);
        --k;
        if (k == 0) {
            this->ans = root->val;
            return;
        }
        revPreOrder(root->left);
    }

    int kthLargest(TreeNode* root, int k) {
        this->k = k;
        revPreOrder(root);
        return ans;
    }
};