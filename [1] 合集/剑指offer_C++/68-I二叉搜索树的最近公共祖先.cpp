#include "header.h"


// 注意所有结点的值需要是唯一的，才能保证有单一解
// 二叉搜索树（BST）的LCA
// 利用二叉搜索树的性质
// 左边结点的比root小，右边结点的比root大
//       6
//    3    8
//   1 5  7 9

// 1 和 5 的 LCA 为3，大小在 1 和 5 之间
// 1 和 8 的 LCA 为6，大小在 1 和 8 之间
// 1 和 3 的 LCA 为3，大小在 1 和 3 之间
// 因此只要遍历该树
// 如果当前结点cur的值均小于要搜索结点的值，那就往右
// 如果当前结点cur的值均大于要搜索结点的值，那就往左
// 如果cur的值在两者之间，就返回cur
class Solution {
public:
    TreeNode* dfs(TreeNode* cur, TreeNode* p, TreeNode* q) {
        if (cur == nullptr) return nullptr;
        if (cur->val > p->val && cur->val < q->val) {
            return cur;
        } else if (cur->val > p->val && cur->val > q->val) {
            dfs(cur->left, p, q);
        } else {
            dfs(cur->right, p, q);
        }
        return nullptr;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || p == nullptr || q == nullptr) return nullptr;
        if (p->val > q->val) swap(p, q);
        return dfs(root, p, q);
    }
};
