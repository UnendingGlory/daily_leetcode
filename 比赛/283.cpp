#include "header.h"


class Solution {
public:
    vector<string> cellsInRange(string s) {
        int rs = s[1] - '0', re = s[4] - '0';
        char cs = s[0], ce = s[3];
        vector<string> ans;
        for (char i = cs; i <= ce; ++i) {
            for (int j = rs; j <= re; ++j) {
                string t = string(1, i) + string(1, j+'0');
                ans.push_back(t);
            }
        }
        return ans;
    }
};


// 向数组中追加k个互不相同且尚未出现的整数，并使结果最小
// [96,44,99,25,61,84,88,18,19,33,60,86,52,19,32,47,35,50,94,17,29,98,22,21,72,100,40,84]
// 35
class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        int cnt = 0, idx = 0, i;
        long long sum = 0;
        for (i = 1; i < nums.back(); ++i) {
            if (cnt >= k || idx >= nums.size()) {
                break;
            }

            if (i == nums[idx]) {
                ++idx;
                continue;
            }

            ++cnt;
            sum += i;
        }
        std::cout << sum << " " << cnt << " " << endl;
        if (cnt < k) {
            for (int j = 0; j < k - cnt; ++j) {
                sum += (i + 1 + j);
            }
        }
        return sum;
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include "binary_tree.h"


class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {    
        unordered_map<int, TreeNode*> v;
        unordered_map<int, int> deg;
        for (auto &d : descriptions) {
            int p = d[0], c = d[1], left = d[2];
            if (!v.count(p))
                v[p] = new TreeNode(p);
            if (!v.count(c))
                v[c] = new TreeNode(c);
            if (left)
                v[p]->left = v[c];
            else
                v[p]->right = v[c];
            deg[c]++; // 判断是否是根结点
        }
        
        for (auto [i, node] : v)
            if (deg[i] == 0)
                return node;
        
        return nullptr;
    }
};

