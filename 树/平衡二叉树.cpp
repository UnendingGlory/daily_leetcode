#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
};

class Solution {
    bool flag = true;
public:
    int getHeight(TreeNode* root)
    {
        if(!root) return 0;
        int l_h = getHeight(root->left), r_h = getHeight(root->right); // 左右子树高度
        if(abs(l_h - r_h) > 1) flag = false;
        return max(l_h, r_h) + 1; // 返回的高度要+1
    }

    bool isBalanced(TreeNode* root) {
        getHeight(root);
        return flag;
    }
};

class Solution {
public:
	bool isBalanced(TreeNode* root)
	{
		if (root == nullptr) return true;
        int depth = 0;
		return get(root, depth);
	}

	bool get(TreeNode* root,int &pDepth) {
		if (root == nullptr) { pDepth = 0; return true; }
		int left=0,right=0;
		if (get(root->left, left) && get(root->right, right))
		{
			int diff = left - right;
			if (abs(diff) <= 1)
			{
				pDepth = 1 + (left > right ? left : right);
				return true;
			}
		}
		return false;
	}
};