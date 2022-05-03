#include "header.h"

struct TNode { // 常规的一棵树
    int                    val;    
    std::vector<TNode*>    child;    
};

// 注意所有结点的值需要是唯一的，才能保证有单一解
// 树的LCA
//        A
//    B      C
//  D E F   G H

// D 和 G 的 LCA 为A
// D 和 E 的 LCA 为B
// B 和 E 的 LCA 为B

// 若是一棵树，那么就不能使用二叉树中的判断p和q落在左右两侧的递归写法了。
// 只能判断p和q是否同时存在于结点 root 的子树中。
// 如果在子树中，则遍历所有的子结点
// 从上到下递归，若一个结点 root 自己的子树中包含p, q
// 但是子结点却不包含，那么 root 就是结果

// 具体的，对于输入 D 和 F
// dfs(A)为false, dfs(B)为true, dfs(D), dfs(E), dfs(F)均为false，返回B
// 对于输入 D 和 G
// dfs(A)为true, dfs(B)为false, dfs(C)为false，返回A

// 递归写法：两层递归
// 时间复杂度较高，因为会重复遍历结点
class Solution {
    TreeNode* ans;
public:
    bool dfs(TNode* root, TNode* p, TNode* q) {
        if (root == nullptr) return fasle;
        if (root == p || root == q) return true;
        int cnt = 0;
        for (int i = 0; i < root->child.size(); ++i) {
            TNode* c = root->child[i];
            cnt += dfs(c, p, q);
        }
        if (cnt == 2) return true;
        if (dfs(root) && cnt == 0) {
            ans = root;
        }
        return false;
    }

    TreeNode* lowestCommonAncestor(TNode* root, TNode* p, TNode* q) {
        if (root == nullptr || p == nullptr || q == nullptr) return nullptr;
        dfs(root, p, q);
        return ans;
    }
};


// Solution2: 只要两次遍历该树。
// 每次遍历得到一条从根结点到搜索结点的链表，如D和F。
// 然后求两条链表的最后一个公共结点即可。(该解法对于普通树也适用）
// A->B->D，A->C->F，最后一个公共结点为A
class Solution {
public:
    bool dfs(TNode* root, TNode* target, vector<TNode*> &path) { // 目标节点
        if (root == target) {
            return true;
        }
        path.emplace_back(root);
        bool found = false;
        for (int i = 0; i < root->child.size(); ++i) {
            found = dfs(c);
        }
        if (!found) { // 未找到就从路径中剔除
            path.pop_back();
        }
        return found;
    }
    TNode* findLastCommonNode(vector<TNode*> path1, vector<TNode*> path2) {
        TNode* ans = nullptr;
        for (int i = 0; i < path1.size() && i < path2.size(); ++i) {
            if (path1[i] == path2[i]) {
                ans = path1[i];
            }
        }
        return ans;
    }
    TNode* lowestCommonAncestor(TNode* root, TNode* p, TNode* q) {
        vector<TNode*> path1, path2;
        dfs(root, p, path1);
        dfs(root, p, path2);
        return findLastCommonNode(root, path1, path2);
    }
};
