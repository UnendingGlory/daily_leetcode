#include "header.h"

// 给你一个二叉树的根节点 root，该二叉树的右节点均没有子结点。
// 请你将此二叉树上下翻转，并返回新的根节点。
// 你可以按下面的步骤翻转一棵二叉树：
// 原来的左子节点变成新的根节点
// 原来的根节点变成新的右子节点
// 原来的右子节点变成新的左子节点
// 上面的步骤逐层进行。题目数据保证每个右节点都有一个同级节点（即共享同一父节点的左节点）且不存在子节点。

// 输入：root = [1, 2, 3, 4, 5]
// 输出：[4, 5, 2, null, null, 3, 1]

// Solution：递归。
// 对于一个结点 root来说，l = root.left, r = root.right
// 翻转之后，l.left = root.right, l.right = root, root.left = null, root.right = null
// 所以在递归时对于一个结点 root来说，只需要知道父亲结点 parent即可。
// 翻转之后，root.left = parent.right, root.right = parent
//         parent.left = nullptr, parent.riht = nullptr
// 递归时，只需要先一直往左递归，再从底向上返回。
// 注意，需要找到翻转后的头结点（即最左边的结点）。
class Solution {
public:
    TreeNode* reversedRoot;
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        reversedRoot = nullptr;
        dfs(root, nullptr);
        return reversedRoot;
    }

    void dfs(TreeNode* root, TreeNode* parent) {
        if (root == nullptr) {
            return;
        }
        dfs(root->left, root);
        if (reversedRoot == nullptr) {
            reversedRoot = root;
        }
        if (parent != nullptr) {
            root->left = parent->right;
            root->right = parent;
            parent->left = nullptr;
            parent->right = nullptr;
        }
    }
};
