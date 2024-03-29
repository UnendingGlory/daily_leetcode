#include "./header.h"
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector <vector <int>> ret;
        if (!root) return ret;
        queue <TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            // 即用q的size记录每一层的个数，不用另外再开队列。
            // 这种BFS便于记录树的每一层个数
            int currentLevelSize = q.size();
            ret.push_back(vector <int> ()); // 每一层新开一个
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                ret.back().push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return ret;
    }
};


// 紧凑版本
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            while(n--) { // 注意是 --n
                auto tmp = q.front();
                q.pop();
                ans.emplace_back(tmp->val);
                if(tmp->left) q.push(tmp->left);
                if(tmp->right) q.push(tmp->right);
            }
        }
        return ans;
    }
};
