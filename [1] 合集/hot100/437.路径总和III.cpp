#include "header.h"
// 给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

// Solution1: 二重递归。
// 1. dfs(root, target)
// dfs(root, target) 代表以 root为根结点的二叉树里结点值之和为 val的路径的个数（root必选）。
// 递归边界：root == nullptr, return 0
// 当前的返回为左右结点递归值之和，注意需要额外判断当前结点值是否就是 target。
// 即 dfs(root, target) = (root.val == target) + dfs(root.left, target - root.val) + 
//                                               dfs(root.right + target - root.val)
// 2. pathSum(root, targetSum) 
// dfs(root, target) 代表以 root为根结点的二叉树里结点值之和为 val的路径的个数（root可选可不选）。
// 当前的返回为 选择当前 root的路径个数 + 不选 root的路径个数。
// 而不选 root的路径个数为选择左右子树之一的个数和。
// 即 pathSum(root, targetSum) = dfs(root, targetSum) + pathSum(root.left, targetSum) +
//                                                      pathSum(root.right, targetSum) 
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;
        return dfs(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
    }
    // target类型需要用 long long，因为 target - root->val 可能溢出
    int dfs(TreeNode *root, long long target) {
        if (root == nullptr) return 0;
        return (root->val == target) + dfs(root->left, target - root->val) +
                                          dfs(root->right, target - root->val);
    }
};

// Solution2: 递归 同时 前缀和。
// sum 代表从根结点到 root（不包含root）的前缀和。
// 遍历到结点 root时，在哈希表中查找是否存在键值 sum - targetSum即可。
// 边递归边统计前缀和。
// dfs(root, sum, target) 代表以 root为根结点的二叉树里结点值之和为 val的路径的个数（root必选）。
class Solution {
public:
    // value类型是int，因为一条路径上可能有多个答案
    unordered_map<long long, int> sum_cnt;
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;
        sum_cnt[0] = 1; // 注意，需要预处理头结点。
        return dfs(root, 0, targetSum);
    }

    // sum 类型需要用 long long，因为前缀和可能溢出。
    int dfs(TreeNode *root, long long sum, int target) {
        if (root == nullptr) return 0;
        sum += root->val; // 当前前缀和
        int ret = 0;
        if (sum_cnt.find(sum - target) != sum_cnt.end()) {
            ret = sum_cnt[sum - target];
        }
        sum_cnt[sum]++;
        ret += dfs(root->left, sum, target);
        ret += dfs(root->right, sum, target);
        sum_cnt[sum]--;
        return ret;
    }
};
