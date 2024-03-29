# 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

# 双指针法。
# 使用双指针，左指针指向当前已经处理好的序列的尾部，右指针指向待处理序列的头部。

# 右指针不断向右移动，每次右指针指向非零数，则将左右指针对应的数交换，同时左指针右移。

# 注意到以下性质：
# 左指针左边均为非零数；
# 右指针左边直到左指针处均为零。
# 因此每次交换，都是将左指针的零与右指针的非零数交换，且非零数的相对顺序并未改变。

# [0,1,0,3,12]
from typing import List
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        l = r = 0
        while r < n:
            if nums[r]:
                nums[l], nums[r] = nums[r], nums[l]
                l += 1
            r += 1
