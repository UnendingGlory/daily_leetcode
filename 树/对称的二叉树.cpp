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

// 判断二叉树是否为对称二叉树
// 思路1: 对称是对于每一层而言，考虑空节点，所以可以考虑层序遍历

class Solution {
    vector<int> ori, mirr;
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        // 树的层序遍历，并用临时列表保存每一层
        const int maxd = 0x3f3f3f3f;
        auto empty_node = new TreeNode(maxd);

        // 层序遍历使用队列
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int current_level_size = q.size();

            auto level_list = vector<int> ();
            for (int i = 1; i <= current_level_size; ++i) {
                auto node = q.front();
                q.pop();
                level_list.emplace_back(node->val);

                if (node != empty_node) {  // 添加判断，否则无限循环
                    if (node->left) q.push(node->left);
                    else q.push(empty_node); // 考虑空节点

                    if (node->right) q.push(node->right);
                    else q.push(empty_node);
                }
            }

            // 检查当前层是否对称
            if (!check(level_list)) return false;
        }
        return true;
    }

    // 双指针检查对称性
    bool check(vector<int>& vec) {
        for (int i = 0, j = vec.size() - 1; i < j; ++i, --j) {
            if (vec[i] != vec[j]) return false;
        }
        return true;
    }
};

// 思路2: 给定两个节点a, b，除开判断条件，若a的左孩子和b的右孩子相等 && a的右孩子和b的左孩子相等
// 则对称
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return check(root->left, root->right);
    }

    bool check(TreeNode* a, TreeNode* b) {
        if (a == nullptr && b == nullptr) return true;
        if (a == nullptr || b == nullptr) return false;
        if (a->val != b->val) return false;
        return check(a->left, b->right) && check(a->right, b->left);
    }
};


