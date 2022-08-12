#include<bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    int isPrefixOfWord(string s, string t) {
        int last = 0, ans = 0;
        for(int i = 1; i <= s.size(); ++i)
        {
            ++ans;
            if(i == s.size() || s[i - 1] == ' ')
            {
                string sub = s.substr(last, i - last);
                if(sub.find(t) == 0) return ans;
                last = i;
            }
        }
        return -1;
    }
};

// T2 slide window
class Solution {
public:
    int maxVowels(string s, int k) {
        set<char> ss{'a', 'e', 'i', 'o', 'u'};
        int ans = 0, preans = 0, res;
        int i, j = k - 1;
        for(i = 0; i <= j; ++i)
        {
            if(ss.find(s[i]) != ss.end()) ++ans;
        }
        res = ans;
        for(i = 1, j = k; j < s.size(); ++i, ++j)
        {
            if(ss.find(s[i - 1]) != ss.end()) --ans;
            if(ss.find(s[j]) != ss.end()) ++ans;
            res = max(ans, res);
        }
        return res;
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

// 遍历的时候计数
class Solution {
public:
    unordered_map<int, int> m;
    int ans = 0;
    void dfs(TreeNode* root)
    {
        // 状态回归
        if(root->left == nullptr && root->right == nullptr)
        {
            ++m[root->val];
            int odd = 0;
            for(auto i : m)
            {
                if(i.second & 1) ++odd;
            }
            if(odd == 0 || odd == 1) ++ans; // 出现奇数数字的个数大于1则一定不是
            --m[root->val];
            return;
        }
        ++m[root->val];
        if(root->left) dfs(root->left);
        --m[root->val]; // recovery
        ++m[root->val];
        if(root->right) dfs(root->right);
        --m[root->val];
    }

    int pseudoPalindromicPaths (TreeNode* root) {
        dfs(root);
        return ans;
    }
};

// T4