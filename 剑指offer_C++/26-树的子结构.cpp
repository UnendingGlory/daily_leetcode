#include "header.h"
#include "binary_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 判断一个树B是否是另外一个A的子结构
// 递归A中的每一个节点，如果该结点的值和B的根结点结点值相同
// 再判断子结构是否包含B


class Solution {
public:

    bool isSub(TreeNode* A, TreeNode *B) {
        if (B == nullptr) return true; // 遍历到B的底部，说明匹配已经完成
        if (A == nullptr || A->val != B->val) return false; // 遍历到A的底部，说明越过了A的叶子结点
        // 如果值相同，再判断子结点是否相同
        return isSub(A->left, B->left) && isSub(A->right, B->right);
    }

    bool isSubStructure(TreeNode* A, TreeNode* B) {
        // 题目约定空树不是任意一棵树的子结构
        if(A == nullptr || B == nullptr) return false;
        // B为以A为根结点的子结构 || B为以A的左子树为根结点的结构
        // 内部两层递归
        return isSub(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};
