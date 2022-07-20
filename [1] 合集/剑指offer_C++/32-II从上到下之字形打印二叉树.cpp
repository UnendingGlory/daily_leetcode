#include "header.h"


// 层序遍历，双端队列，奇数层孩子放入队头，偶数层放入队尾

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(root == NULL) return result;
        queue<TreeNode*> que;
        que.push(root);
        int level = 0;
        while(!que.empty()) {
            int len = que.size();//这里先存储了每一层数组的大小
            result.push_back(vector<int>(len));//首先根据每层数组大小进行预定义大小

            for(int i = 0; i < len; ++i) {
                TreeNode* cur = que.front();
                que.pop();
                if(level % 2 == 0) {//根据奇偶层进行从前到后或者从后向前的赋值
                    result[level][i] = cur->val;
                } else {
                    result[level][len-i-1] = cur->val;
                }
                if(cur->left) que.push(cur->left);
                if(cur->right) que.push(cur->right);
            }
            ++level;
        }
        return result;
    }
};