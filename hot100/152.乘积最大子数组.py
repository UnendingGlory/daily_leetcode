# 找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
from typing import List

# 根据最大子序和，很容易推导出这样的状态转移方程：
# dp[i] = max(dp[i-1]*nums[i], nums[i])
# 但是这样是错误的，因为对于乘法，当前位置的最优解不一定由前一个位置的最优解得到。
# 比如 a = [5, 6, -3, 4, -3], dp = {5, 30, -3, 4, -3}
# 这样可以得到答案是 30，但是正确答案应该是所有数字的乘积。

# Solution: 根据正负性分类讨论
# 如果当前位置是一个 负数的话，我们希望 dp[i-1] 也是一个负数，且负的尽量多。
# 如果当前位置是一个 正数的话，我们希望 dp[i-1] 也是一个正数，且正的尽量多。
# 我们可以再维护一个 dp_min，表示以第 i 个元素结尾的最小乘积的子数组的乘积。
# 总结一下正负的情况，我们可以得到以下转移方程。
# dp_max[i] = max(dp_max[i-1]*nums[i], dp_min[i-1]*nums[i], nums[i])
# dp_min[i] = min(dp_max[i-1]*nums[i], dp_min[i-1]*nums[i], nums[i])
# ans 为 dp_max 中的最大值
# 边界条件：dp_max[0] = nums[0], dp_min[0] = nums[0]

class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        n = len(nums)
        dp_max = [0] * n
        dp_min = [0] * n
        ans = dp_max[0] = dp_min[0] = nums[0]
        for i in range(1, n):
            dp_max[i] = max(dp_max[i-1]*nums[i], max(dp_min[i-1]*nums[i], nums[i]))
            dp_min[i] = min(dp_max[i-1]*nums[i], min(dp_min[i-1]*nums[i], nums[i]))
            ans = max(ans, dp_max[i])
        return ans
