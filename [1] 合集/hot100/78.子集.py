# 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
from typing import List

# Solution1：迭代法。
# 那迭代的上界如何定呢？即有几种情况呢？
# 如果数组大小为 n，那么每个元素可以选和不选，所以共有 2^n 种可能性。
# [1, 2, 3], n = 3, 共有 8 种可能，即 0 - 7。
# 0 - 7 的二进制位即对应每个元素选或者不选，利用这点结合位运算进行计算。
# 时间复杂度：O(n * 2^n)
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        mask, mask_max = 0, 1 << n
        ans = []
        while mask < mask_max:
            l = []
            for i in range(n):
                if mask & (1 << i) != 0: # 对应位是否为1
                    l.append(nums[i])
            ans.append(l)
            mask += 1
        return ans

# Solution2：递归法。
# 从头到尾，每个位置选或者不选。
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        ans, path = [], []
        def dfs(i):
            if i == n:
                ans.append(path[:]) # 深拷贝
                return
            dfs(i + 1) # 跳过该位置
            
            path.append(nums[i]) # 选择该位置
            dfs(i + 1)
            path.pop()

        dfs(0)
        return ans

