from turtle import Turtle
from typing import List

# 将正整数数组分割成两个子集，使得两个子集的和相等。
# 可以将该问题转化为：从该数组中选出若干数，使得和为整个数组和的一半 target。
# 因此可以先做以下判断：
# 1. 若数组和为奇数，返回 false。
# 2. 若数组中最大的元素 maxNum > target，由于 maxNum + remain = 2target
#    因此 remain < target，即数组中剩余的一半元素和 小于 target。
#    因此也可以直接返回 false。

# Solution1: 01背包动态规划。
# 创建二维数组 dp，共有 n行 target + 1列。
# dp[i][j] 代表从数组的 [0, i] 范围内选取若干数（可以不选），是否能够等于 j。
# 根据 j和 nums[i]的大小关系进行判断：
# 1. 若 j < nums[i]，那么 nums[i]不能选，dp[i][j] = dp[i - 1][j]。
# 2. 若 j >= nums[i]，那么 nums[i]可以选也可以不选。
#    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]]。
# 边界条件：dp[i][0] = true, 
#         i = 0时，只有nums[0]可选，dp[0][nums[0]] = true，其他的 dp[0][j] = False。
# 返回：dp[n-1][target]
# 时间复杂度：O(n * target)，空间复杂度 O(n * target)。
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        sum, max_num = 0, 0
        for num in nums:
            sum += num
            max_num = max(max_num, num)
        if sum & 1: # 奇数
            return False
        target = (sum >> 1)
        if max_num > target:
            return False
        dp = [[False] * (target+1) for _ in range(n)]
        for i in range(n):
            dp[i][0] = True
        dp[0][nums[0]] = True # 判断 2已经保证了数组中的值均<= target
        for i in range(1, n):
            for j in range(1, target+1):
                if j < nums[i]:
                    dp[i][j] = dp[i-1][j]
                else:
                    dp[i][j] = dp[i-1][j] | dp[i-1][j-nums[i]]
        return dp[n-1][target]


# Solution2: 空间复杂度优化。
# 由于每个状态都只跟dp[i-1]相关，因此我们只需要存储一行即可。
# 但是需要对于 j，需要上一个状态时 j - nums[i]位置的 dp值。
# 所以我们需要从大到小进行遍历，这样才不会覆盖之前的值。
# 转移方程：j >= nums[i], dp[j] = dp[j] | dp[j - nums[i]]。
#         j < nums[i], dp[j] = dp[j]。
# 边界条件：dp[0] = dp[nums[0]] = True
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        sum, max_num = 0, 0
        for num in nums:
            sum += num
            max_num = max(max_num, num)
        if sum & 1:
            return False
        target = (sum >> 1)
        if max_num > target:
            return False
        dp = [False for _ in range(target+1)]
        dp[0] = dp[nums[0]] = True
        for i in range(1, n):
            num = nums[i]
            for j in range(target, num-1, -1):
                dp[j] = dp[j] | dp[j - num]
            # 对于 j < nums[i]，由于 dp[j] = dp[j]，所以不需要更新。
        return dp[target]
