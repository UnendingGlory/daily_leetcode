# 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
from typing import List


# Solution: 位运算，对于每一位来说，相同的数异或为0，不同的数异或为1。
# 所以对数组中所有的数做异或即可得到答案。
class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        ans = 0
        for num in nums:
            ans ^= num
        return ans
