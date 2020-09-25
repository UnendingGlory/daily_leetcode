#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 递归，二叉搜索树，生成1-n, 如果根节点为i，则左子树生成1到i-1，右子树生成i+1到n

class Solution {
public:

    // 从start生成到end
    vector<TreeNode*> recur(int start, int end)
    {
        if(start > end) return {nullptr};
        vector<TreeNode*> allTrees;
        // 枚举根节点
        for(int i = start; i < end; ++i)
        {
            // 生成左子树
            vector<TreeNode*> left = recur(start, i - 1);
            // 生成右子树
            vector<TreeNode*> right = recur(i + 1, end);
            // 左子树中选一颗，右子树中选一颗，每种进行拼接，得到最终结果
            for(auto &l : left)
            {
                for(auto &r : right)
                {
                    TreeNode *root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    allTrees.emplace_back(root);
                }
            }
        }
        return allTrees;
    }

    vector<TreeNode*> generateTrees(int n) {
        return recur(1, n);
    }
};