#include "header.h"

// 注意所有结点的值需要是唯一的，才能保证有单一解
// 二叉树的LCA
// 二叉树的值就没有规律了
//       A
//     B   C
//    D E F G

// D 和 F 的 LCA 为A
// D 和 E 的 LCA 为B
// B 和 E 的 LCA 为B

// Solution: 
// 若root是 p和q 的LCA，只可能是以下几种情况之一
// 1. p 和 q分属 root的 两侧 （即左、右子树中）
// 2. p = root, q在root的左或者右子树中
// 3. q = root, p在root的左或者右子树中
// 考虑通过递归对二叉树进行先序遍历，当遇到节点 p 或 q 时返回。
// 从底至顶回溯，当节点 p, q 在节点 root 的异侧时，节点 root 即为最近公共祖先
// 则向上返回 root 。

// 递归写法：
// 当root穿过叶结点，直接返回nullptr
// 若root = p 或者 root = q， 返回 root
// 使用left 和 right 记录root的左侧和右侧返回
// 1. 若left和right同时为空，返回空
// 2. 若left和right同时不为空，即p和q在root两侧，返回root
// 3. 若left为空，right不为空，有两种情况
//    * p和q的其中一个在root右子树中，另一个指向 right
//    * p和q的两个都在root右子树中，此时right为 p 和 q 的 LCA
//    综合起来，若left为空，right不为空，直接返回right
// 4. 若right为空，left不为空，返回left
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        // 以下写法合并了4种情况
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        return root;
    }
};
