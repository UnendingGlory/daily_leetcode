# 不能使用除法
from typing import List

# Solution1：左右乘积数组。
# 建立两个数组，left 和 right。
# left 记录除了位置i，左侧的乘积。
# right 记录除了位置i，右侧的乘积。
# 时间复杂度：O(n)，空间复杂度：O(n)
class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        left = [1 for _ in range(n)]
        right = [1 for _ in range(n)]
        for i in range(1, n):
            left[i] = left[i-1] * nums[i-1]
        for i in range(n-2, -1, -1):
            right[i] = right[i+1] * nums[i+1]
        ans = []
        for i in range(n):
            ans.append(left[i] * right[i])
        return ans


# Solution2：空间复杂度优化。
# 优化为 O(1)，使用结果数组进行保存。
# 使用中间变量保存乘积结果。
class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [1]
        for i in range(1, n):
            ans[i] = ans[i-1] * nums[i-1]
        temp = 1
        for i in range(n-2, -1, -1):
            temp *= nums[i+1]
            ans[i] *= temp
        return ans
