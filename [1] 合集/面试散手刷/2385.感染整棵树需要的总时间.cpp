#include "header.h"

// 给你一棵二叉树的根节点 root ，二叉树中节点的值 互不相同 。另给你一个整数 start 。
// 在第 0 分钟，感染 将会从值为 start 的节点开始爆发。
// 每分钟，如果节点满足以下全部条件，就会被感染：
// 节点此前还没有感染。
// 节点与一个已感染节点相邻。
// 返回感染整棵树需要的分钟数。
// 树中节点的数目在范围 [1, 10^5] 内，1 <= Node.val <= 10^5

// Solution1: 对整棵树建图，建图后进行最短路算法（宽搜）即可。
// 由于结点值各不相同且在 10^5内，因此可以将值作为下标建树。
// 返回所有结点到 start的最短路中的最大值。
// 时间复杂度: O(kE)，k是平均进队次数。
const int maxn = 100005;
class Solution {
public:
    vector<int> graph[maxn]; // 无向图邻接表
    int idx = 0; // 图计数
    void addEdge(int a, int b) {
        graph[a].push_back(b);
        graph[b].push_back(a);    
    }

    void dfs(TreeNode* root) {
        if (root->left) {
            addEdge(root->val, root->left->val);
            addEdge(root->left->val, root->val);
            dfs(root->left);
        }
        if (root->right) {
            addEdge(root->val, root->right->val);
            addEdge(root->right->val, root->val);
            dfs(root->right);
        }
    }

    int amountOfTime(TreeNode* root, int start) {
        dfs(root);
        // 直接 SPFA (图的BFS)
        int dis[maxn]; // 每一个点到起点的最短路
        bool inque[maxn];
        memset(dis, 0x3f3f3f3f, sizeof(dis));
        memset(inque, 0, sizeof(inque));
        dis[start] = 0;
        inque[start] = true;
        queue<int> q;
        q.push(start);

        int ans = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ans = max(ans, dis[u]);
            // 枚举每一个邻点
            for (int i = 0; i < graph[u].size(); ++i) {
                int v = graph[u][i];
                // 通过 u来更新 v
                if (!inque[v]) {
                    if (dis[u] + 1 < dis[v]) {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                        inque[v] = true;
                    }
                }
            }
        }
        return ans;
    }
};

// Solution2: DFS，如果某个结点是根结点，且是起始结点，那么感染整棵树要的最短时间就是树高。
//                 否则，感染整棵树要的最短时间是 根节点到起始结点高度 h1 + 另一棵子树的高度 h2。
// 以上两种情况是并行进行的，两者取最大的即可。
// dfs表示感染以 root为根结点的树所需的最短时间，从上往下递归，从下往上回溯。
// 还是比较难写的。
// 时间复杂度：O(n)
class Solution {
public:
    int ans = 0;
    int depth = -1; // 根结点到起点结点的深度
    int amountOfTime(TreeNode* root, int start) {
        dfs(root, 0, start);
        return ans;
    }

    // 返回树高，level记录原树的根结点到 root的深度
    int dfs(TreeNode* root, int level, int start) {
        if (root == nullptr) {
            return 0;
        }
        if (root->val == start) {
            depth = level;
        }
        int l = dfs(root->left, level + 1, start);
        bool inLeft = (depth == -1) ? false : true; // 起始结点是否在左子树中 
        int r = dfs(root->right, level + 1, start);

        if (root->val == start) {
            ans = max(ans, max(l, r)); // 感染以 start为根结点的树所需的时间
        }
        if (inLeft) { // 在左子树中
            ans = max(ans, depth - level + r);
        } else {
            ans = max(ans, depth - level + l);
        }
        
        return max(l, r) + 1;
    }
};
