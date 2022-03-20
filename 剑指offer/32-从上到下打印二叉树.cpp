#include "header.h"


// 层序遍历
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
      if (root == nullptr) return {};
      vector<vector<int>> ans;

      queue<TreeNode *> q;
      q.push(root);
      while (!q.empty()) {
        int currentLevelSize = q.size();
        vector<int> vec;

        for (int i = 0; i < currentLevelSize; ++i) {
          auto tmp = q.front();
          q.pop();

          vec.emplace_back(tmp->val);

          if (tmp->left) q.push(tmp->left);
          if (tmp->right) q.push(tmp->right);
        }
        
        ans.emplace_back(vec);
      }
      return ans;
    }
};
