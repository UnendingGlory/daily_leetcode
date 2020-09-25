#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    // 只包含一种字符串的最大长度
    int maxPower(string s) {
        char cur = s[0];
        int l = 0, ans = 0;
        for(int i = 0; i < s.size(); ++i)
        {
            if(s[i] == cur) ++l;
            else
            {
                cur = s[i];
                l = 1;
            }
            ans = max(ans, l);
        }
        return ans;
    }
};

// T2
class Solution {
public:
    int gcd(int x, int y) // 求两者最大公约数
    {
        if(x == 1 || y == 1) return 1;
        if(y == 0) return y;
        return gcd(y, x % y);
    }

    vector<string> simplifiedFractions(int n) {
        vector<string> ans;
        for(int i = n; i >= 2; --i)
        {
            ans.push_back("1/" + to_string(i));
            for(int j = 2; j < n; j++)
            {
                if(gcd(i, j)  == 1) 
                    ans.push_back(to_string(j) + "/" + to_string(i));
            }
        }
        return ans;
    }
};

// T3
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 从根到该节点的过程中，没有任何节点值大于它
class Solution {
public:
    int ans = 0;
    // 先根遍历，中间存储最大值即可
    void pre(TreeNode* root, int max)
    {
        if(root == nullptr) return;
        if(root->val >= max)
        {
            ++ans;
            max = root->val;
        }
        if(root->left) pre(root->left, max);
        if(root->right) pre(root->right, max);
    }

    int goodNodes(TreeNode* root) {
        pre(root, INT_MIN);
        return ans;
    }
};