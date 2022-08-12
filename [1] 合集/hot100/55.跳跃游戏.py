# 你最初位于数组的第一个下标，每个元素代表你在该位置可以跳跃的最大长度。
# 判断你是否能够到达最后一个下标。

# 贪心算法。
# 如果 x 是一个可以到达的位置，那么 x + nums[i] 也是可以到达的位置。
# 维护一个变量 mostright，动态更新即可。
from typing import List

class Solution:
    def canJump(self, nums: List[int]) -> bool:
        n = len(nums)
        most_right = 0
        for i in range(n):
            if i <= most_right and nums[i] + i >= most_right:
                most_right = nums[i] + i
                if most_right >= n - 1:
                    return True
        return False

 