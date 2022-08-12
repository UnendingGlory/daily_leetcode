#include "header.h"

// 给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
// candidates 中的每个数字在每个组合中只能使用 一次 。
// 注意：解集不能包含重复的组合。 
// 与 39题不同的是，该题每个数字在每个组合中只能使用一次。

// Solution：循环式递归 + 剪枝。
// 需要先对数组进行排序。
// 和全排列II、子集II类似，都是重复则剪枝。
// 对于数字 x，如果前面有相同的数 y，且 y没有被选择，则应该被跳过。
class Solution {
public:
    vector<int> path;
    vector<vector<int>> ans;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, target);
        return ans;
    }
    
    void dfs(vector<int> &candidates, int idx, int remain) {
        if (remain == 0) {
            ans.push_back(path);
        }

        // 往后循环。
        for (int i = idx; i < candidates.size() - 1; ++i) {
            int residue = remain - candidates[i];
            if (residue < 0) {
                break;
            }
            // 跳过重复数。
            // 如果 i = idx, 那么可以进入下一个数，可以选择下一个重复的数 y。
            // 如果 i > idx, 那么代表数字 x之前有相同的数 y没有被选择，应该跳过。
            if (i > idx && candidates[i] == candidates[i - 1]) {
                continue;
            }
            
            path.push_back(candidates[i]);
            // 跳到 i + 1个数。
            dfs(candidates, i + 1, residue);
            path.pop_back();
        }
    }
};
