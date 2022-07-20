#include "header.h"
// 判断一个二叉树是否和其镜像相同


// Solution1: 层序遍历然后判断每一层是否对称
// 注意，这里层序遍历需要考虑空结点
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        queue<TreeNode *> q;
        auto emptyNode = new TreeNode(INT_MAX);
        q.push(root);
        while(!q.empty()) {
            auto vec = vector<int> {}; // 每一层使用一个临时vector保存
            int c = q.size();
            for (int i = 0; i < c; ++i) {
                auto tmp = q.front();
                q.pop();
                vec.emplace_back(tmp->val);

                if (tmp != emptyNode) { // 添加判断，否则无限循环
                    if (tmp->left) q.push(tmp->left);
                    else q.push(emptyNode);

                    if (tmp->right) q.push(tmp->right);
                    else q.push(emptyNode);
                }
            }
            if (!check(vec)) return false;
        }
        return true;
    }
    
    bool check(vector<int> &vec) { // 检查是否对称
        for (int i = 0, j = vec.size() - 1; i < j; ++i, --j) {
            if (vec[i] != vec[j]) {
                return false;
            }
        }
        return true;
    }
};


// Solution2: 递归判断,结点A和B，A的左孩砸和B的右孩砸,A的右孩砸和B的左孩砸是否相等
class Solution {
public:
    bool recur(TreeNode* A, TreeNode* B) {
        if (A == nullptr && B == nullptr) return true;
        if (A == nullptr || B == nullptr) return false;
        if (A->val != B->val) return false;
        return recur(A->left, B->right) && recur(A->right, B->left);
    }

    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return recur(root->left, root->right);
    }
};
