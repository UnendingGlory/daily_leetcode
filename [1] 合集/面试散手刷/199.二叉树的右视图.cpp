#include "header.h"

// 给定一个二叉树的根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

// Solution1：递归，其实就是输出每一层最右侧的结点。
// 按照 根结点 -> 右节点 -> 左节点的过程的部分遍历。
// 递归过程中需要记录结点的当前所在层是否已经有结果存储，如果有的话则不能加入结果数组。
// 为了达到该目的，递归时需要记录当前结点的高度。
// 可以用结果数组当前的大小来方便的记录每一层是否已经有数存储。
// 时间复杂度：O(n)，空间复杂度：O(n)。
class Solution {
public:
    vector<int> ans;
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        dfs(root, 0);
        return ans;
    }

    void dfs(TreeNode *root, int depth) {
        if (root == nullptr) {
            return;
        }
        if (ans.size() == depth) {
            ans.push_back(root->val);
        }
        dfs(root->right, depth + 1);
        dfs(root->left, depth + 1);
    }
};

// Solution2: 直观思路，BFS，记录每一层最后一个结点即可。
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        queue<TreeNode *> q; // BFS需要一个队列
        q.push(root);
        vector<int> ans;
        while (!q.empty()) {
            int curLevelSize = q.size();
            for (int i = 0; i < curLevelSize; ++i) {
                TreeNode* p = q.front();
                q.pop();
                if (i == curLevelSize - 1) {
                    ans.push_back(p->val);
                }
                if (p->left) {
                    q.push(p->left);
                }
                if (p->right) {
                    q.push(p->right);
                }
            }
        }
        return ans;
    }
};
