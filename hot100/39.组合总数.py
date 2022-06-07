from typing import List
import copy
# 无重复元素 的整数数组 candidates 和一个目标整数 target。
# 找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。
# 同一个数字可以被重复选择。
# 输入：[2,3,6,7]，目标：7
# 输出：[[2, 2, 3], [7]]

# Solution1：递归 + 回溯
import copy
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        n = len(candidates)
        ans, tmp = [], []
        def dfs(cur, remain):
            if cur == n:
                return
            
            if remain == 0:
                ans.append(copy.deepcopy(tmp))
                return
            
            # 可以重复选取当前元素
            if remain - candidates[cur] >= 0:
                tmp.append(candidates[cur])
                dfs(cur, remain - candidates[cur])
                tmp.pop()

            # 跳过当前元素，不需要append
            dfs(cur + 1, remain)
        
        dfs(0, target)
        return ans

# Solution2：递归 + 回溯 + 排序剪枝
# 采用循环式递归。
# 排序数组的话，后序的都不用再递归。
# 要注意写法， 避免重复结果出现
from typing import List
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        n = len(candidates)
        if n == 0:
            return []
        candidates.sort()
        path, res = [], []

        def dfs(begin, remain):
            if remain == 0:
                res.append(copy.deepcopy(path))
                return

            for index in range(begin, n):
                residue = remain - candidates[index]
                if residue < 0:
                    break
                
                path.append(candidates[index])
                dfs(index, residue)
                path.pop()

        dfs(0, target)
        return res


# Solution3：给定 Capcity 情况下，求解最大的 Value 背包问题

if __name__ == "__main__":
    s = Solution()
    candidates = [2,3,6,7]
    target = 7
    ans = s.combinationSum(candidates, target)
    print(ans)
