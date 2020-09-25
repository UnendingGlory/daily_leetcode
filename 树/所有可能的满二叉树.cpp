#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 满二叉树节点数一定是奇数
class Solution {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        vector<TreeNode*> res;
        if (N % 2 == 0) return res;//偶数或者0时递归要返回了
        if (N == 1){
            res.push_back(new TreeNode(0));
            return res;
        }
        for(int i = 1; i <= N - 2; i += 2){//遍历所有可能的左右分配情况
            vector<TreeNode*> left;
            vector<TreeNode*> right;
            left = allPossibleFBT(i);//找到所有可能的左子树，若生成左子树，则必须要生成右子树
            right = allPossibleFBT(N - i - 1);//找到所有可能的最右子树
            for (int j = 0; j < left.size(); ++j){//总共有left.size()*right.size()的情况，全部遍历生成
                for (int k = 0; k < right.size(); ++k){
                    TreeNode* root = new TreeNode(0);
                    root->left = left[j];
                    root->right = right[k];
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};

int main()
{
    return 0;
}