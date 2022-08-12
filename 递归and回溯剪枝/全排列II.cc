#include "header.h"
using namespace std;

// 类似 剑指offer38、子集II、组合总数 II
// 1. 使用排序 + 判重跳过相同的数字
//    对于数字 x，如果有前面相同的数字 y且 y没有被访问，应该跳过该数。
// 2. 也可以使用一个哈希表存储递归中遍历到的数字，并判断数字是否重复。
//    空间换时间，节省了排序时间。
class Solution {
    vector<int> vis;

public:
    void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
        if (idx == nums.size()) {
            ans.emplace_back(perm);
            return;
        }
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
                continue;
            }
            perm.emplace_back(nums[i]);
            vis[i] = 1;
            backtrack(nums, ans, idx + 1, perm);
            vis[i] = 0;
            perm.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> perm;
        vis.resize(nums.size());
        sort(nums.begin(), nums.end());
        backtrack(nums, ans, 0, perm);
        return ans;
    }
};