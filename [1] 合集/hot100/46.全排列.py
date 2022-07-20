from typing import List
import copy
# 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案
# 注意这里数字是不重复的，重复的情况见：剑指offer 38

# 直接思路，递归
# 对于每一个位置，考虑枚举每个值
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        path, ans = [], []

        visit = [False for _ in range(n)]  # 记录每个数字是否被使用
        def dfs(idx):
            if idx == n:
                ans.append(copy.deepcopy(path))
                return
            for i in range(n):
                if visit[i] == False:
                    path.append(nums[i])
                    visit[i] = True
                    dfs(idx + 1)
                    visit[i] = False # 记得重置
                    path.pop()
        dfs(0)
        return ans

# 递归 + 交换实现，在原数组上实现，避免vis数组空间复杂度消耗
# 改写递归写法，将每一个元素固定在第 x 位
# idx = 0：交换 n 次
# idx = 1：交换 n - 1次
# ...
# idx = n - 1，递归出口
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        ans = []

        def dfs(idx):
            if idx == n - 1:
                # 这样写是深拷贝，如果写成 nums，那么是浅拷贝，最终结果会出错。
                # 或者：copy.deepcopy(nums)。
                ans.append(nums[:]) 
                return
            for i in range(idx, n):
                nums[i], nums[idx] = nums[idx], nums[i]
                dfs(idx + 1)
                nums[i], nums[idx] = nums[idx], nums[i] # 递归完交换回来
        dfs(0)
        return ans
