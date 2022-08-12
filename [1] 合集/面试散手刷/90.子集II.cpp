#include "header.h"

// 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
// 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
// 与 78题 [子集] 类似，不同的是该题中数组可能包含重复的元素。
// 输入：nums = [1,2,2]
// 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]

// Solution1: 迭代 + 位置标记（类似于全排列 II、组合总数 II）
// 先对数组进行排序。
// 对于[1, 2, 2]， 选择前两个数，或者选择第一和第三个数会得到重复结果。
// 对于第二个 2来说，如果第一个 2在当前没有被选择，那么就会产生重复结果。
// 即对于数 x来说，如果前面有相同的数字 y，且 y没有被选择，那么就会得到重复结果，应该跳过。
// 迭代法用二进制位来标记每一个数是否被选择。
// 用图思考清楚数组下标和位运算之间的关系。
//    2 2 1 (数组元素)
//    2 1 0 (数组下标)
// 0: 0 0 0
// 1: 0 0 1
// 2: 0 1 0 
// ...
// 7: 1 1 1
// 迭代上界：2^n - 1
// 时间复杂度：O(n * 2^n)
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int mask = 0, mask_max = (1 << n);
        vector<vector<int>> ans;
        vector<int> path;
        while (mask < mask_max) {
            path.clear();
            bool flag = false;
            for (int i = 0; i < n; ++i) {
                if ((mask & (1 << i)) != 0) {
                    if (i > 0 && ((mask >> (i - 1)) & 1) == 0 && nums[i] == nums[i - 1]) {
                        flag = true;
                        break;
                    }
                    path.push_back(nums[i]);
                }
            }
            if (!flag) {
                ans.push_back(path);
            }
            ++mask;
        }
        return ans;
    }
};

// Solution2: 递归，同样思路。
// 对于数 x来说，如果前面有相同的数字 y，且 y没有被选择，则会得到重复的结果，应该跳过。
// 递归，对每一个数可以选，也可以不选。
// 空间复杂度高于迭代，因为用到了递归栈。
class Solution {
public:
    vector<int> path;
    vector<vector<int>> ans;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        dfs(false, nums, 0);
        return ans;
    }
    
    // preChosen标记上一个数是否被选择
    void dfs(bool preChosen, vector<int> &nums, int idx) {
        if (idx == nums.size()) {
            ans.push_back(path);
            return;
        }

        // 忽略该位置
        dfs(false, nums, idx + 1);
        if (idx > 0 && !preChosen && nums[idx] == nums[idx - 1]) {
            return;
        }
        
        // 选择该位置
        path.push_back(nums[idx]);
        dfs(true, nums, idx + 1);
        path.pop_back();
    }
};
