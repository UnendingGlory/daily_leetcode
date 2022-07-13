# include "header.h"

// 和198类似，不同偷窃相邻的房屋，不同的是，
// 这次数据结构换成了二叉树，不能偷窃相邻的二叉树结点。

// Solution1: 二叉树上的动态规划（可记忆化）。
// 使用 f保存如果偷窃该结点，以 root为根的二叉树里最多能偷窃到的值。
// 使用 g保存如果不偷窃该结点，以 root为根的二叉树里最多能偷窃到的值。
// 对于某结点 node，可以选择。
// 1. 偷窃该结点，那么子结点就不能被偷窃，f(node) = node.val + g(node.left) + g(node.right)
// 2. 不偷窃该结点，那么可以选择偷窃子结点，也可以选择不偷窃子结点。
//    g(node) = max{ f(node.left), g(node.left) } + max{ f(node.right), g(node.right) }
// 最终返回结果为 max(f(root), g(root))

// 需要使用哈希表来保存 f和 g的中间结果。
// 由于父结点需要用到左右子结点处理的结果，因此适合后序遍历，减少重复计算。
// 时间复杂度：O(n)，空间复杂度：O(n)。
class Solution {
public:
    unordered_map <TreeNode*, int> f, g; // 默认值为0
    int rob(TreeNode* root) {
        dfs(root);
        return max(f[root], g[root]);
    }

    void dfs(TreeNode *node) {
        if (node == nullptr) return;
        dfs(node->left);
        dfs(node->right);
        f[node] = node->val + g[node->left] + g[node->right];
        g[node] = max(f[node->left], g[node->left]) + max(f[node->right], g[node->right]);
    }
};

// Solution2: 空间复杂度优化。
// 做一个小小的优化，每个结点的状态只取决于 f(node.left), f(node.right), g(node.left), g(node.right)。
// 可以设计一个结构，表示某个节点的 f和 g值，在每次递归返回，将该点返回上一级调用。
// 可以省略一个哈希表的空间。
struct Node { // 结点的 f和 g值
    int f, g;
};

class Solution {
public:
    int rob(TreeNode* root) {
        auto rootNode = dfs(root);
        return max(rootNode.f, rootNode.g);
    }

    Node dfs(TreeNode* node) {
        if (node == nullptr) {
            return {0, 0};
        }
        auto l = dfs(node->left);
        auto r = dfs(node->right);
        int f = node->val + l.g + r.g;
        int g = max(l.f, l.g) + max(r.f, r.g);
        return {f, g};
    }
};
