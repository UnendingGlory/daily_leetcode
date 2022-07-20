# 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的连续子数组的个数 。
# 输入：nums = [1,1,1], k = 2； 输出：2。
# 输入：nums = [1,2,3], k = 3； 输出：2。

import collections
from gc import collect
from typing import List

# Solution1: 枚举。
# 枚举 0...n-1，i代表连续子数组的终点。
# 再倒着枚举 i...0，j代表连续子数组的起点。
# 对于 [j-1, i] 的和可以使用 [j, i]推出。
# 时间复杂度：O(n^2)，空间复杂度：O(1)。
# 可能会超时。
class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ans = 0
        for i in range(n):
            sum = 0
            for j in range(i, -1, -1):
                sum += nums[j]
                if sum == k:
                    ans += 1
        return ans


# Solution2：前缀和 + 哈希表。
# 对 Solution1方法可以使用前缀和数组来进行优化。
# [j, i] 之和可以使用 pre[i] - pre[j-1]来表示。
# pre[i] - pre[j-1] = k
# pre[j-1] = pre[i] - k。
# 对于下标 i，只需要去寻找前面位置多少个元素前缀和为 pre[i] - k即可。
# 因此可以使用一个哈希表预处理，可以将两个逻辑合在一个循环中使用。
# 时间复杂度：O(n)，空间复杂度：O(n)。
import collections
class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        n = len(nums)
        sum = collections.defaultdict(int)
        sum[0] = 1 # 和为0的个数为1
        pre, ans = 0, 0
        for i in range(n):
            pre += nums[i]
            if pre - k in sum:
                ans += sum[pre-k]
            sum[pre] += 1
        return ans
