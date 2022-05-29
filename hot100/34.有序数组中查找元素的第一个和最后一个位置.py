from typing import List

# 排序数组中存在重复数字，查找目标target第一个和最后一个位置
# 和 剑指offer 53题类似
# 要求时间复杂度 O(logn)

# nums = [5,7,7,8,8,10], target = 8, ans: [3, 4]
# nums = [5,7,7,8,8,10], target = 6, ans: [-1, -1]

# 二分，查找第一个等于该元素的位置 和 第一个大于该元素的位置-1
# 即查找第一个大于等于该元素的位置 和 第一个大于该元素的位置-1
# 即可以得到答案

class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        n = len(nums)
        # 查找第一个大于 或 大于等于 的二分模板合并
        # is_gt，is greater equal 是否是 大于等于
        def binarySearch(l, r, is_ge):
            # 返回值 ans 设置为 n，作用有二
            # 1. 比如 [1], target = 1，那么 is_gt 为 True时 返回 n
            #    idx2 = n - 1 就返回 0， 设置为其他值答案可能会错误
            # 2. 确保了返回值大于0
            ans = n
            while l <= r:
                mid = r + ((l - r) >> 1)
                if nums[mid] > target or (is_ge and nums[mid] >= target):
                    ans = mid
                    r = mid - 1
                else:
                    l = mid + 1
            return ans

        idx1 = binarySearch(0, n - 1, True)
        idx2 = binarySearch(0, n - 1, False) - 1
        if idx1 < n and idx2 < n and nums[idx1] == target and nums[idx2] == target:
            return [idx1, idx2]
        else:
            return [-1, -1]
        