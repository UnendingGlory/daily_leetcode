#include <binary_tree.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


// 深度优先或者广度优先
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }

    // 利用值传递
    int dfs(TreeNode *root, int pre_sum)
    {
        if(root == nullptr) return;
        // 关键点，将前面节点的值*10
        int sum = pre_sum * 10 + root->val;
        // 如果是叶子节点直接return
        if(root->left == nullptr && root->right == nullptr)
            return sum;
        else
        {
            return dfs(root->left, sum) + dfs(root->right, sum);
        }
    }
};