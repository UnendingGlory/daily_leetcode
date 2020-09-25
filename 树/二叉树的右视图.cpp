#include <bits/stdc++.h>
using namespace std;

struct TreeNode 
{     
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


// 二叉树的右视图，即输出每一层的最右侧的节点加入ans中
// 层次遍历，开两个队列
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(root == nullptr) return {};
        vector<int> ans;
        queue<TreeNode*> q;
        queue<int> height;
        q.push(root);
        height.push(0);
        while(!q.empty())
        {
            auto temp = q.front();
            int h = height.front();
            q.pop(), height.pop();
            if(q.empty() || height.front() == h + 1) ans.push_back(temp->val);
            if(temp->left) q.push(temp->left), height.push(h + 1);
            if(temp->right) q.push(temp->right), height.push(h + 1);
        }
        return ans;
    }
};

// 也可以用size记录每层的数量