from typing import List

# 即数组的前半段和后半段是分组升序的，数组中每一个值都唯一。
# 要求在O(logn)的时间复杂度内，查找到目标数值。

# 将数组一分为二，其中一定有一个是有序的，另一个可能是有序，也能是部分有序。
# 此时有序部分用二分法查找。
# 对于无序部分，再一分为二，其中一个一定有序，另一个可能有序，可能无序。
# 如此循环。

# 例子：
# [4, 5, 6, 7, 0, 1, 2], l = 0, r = 6, mid = 3, nums[mid] = 7
# 若 target = 5，左半边是有序的，target落在有序的左半边内，则在 [l, mid - 1] 中查找。
# 若 target = 2，target落在无序的右半边内，则在 [mid + 1, r] 中查找。

# [6, 7, 0, 1, 2, 4, 5], l = 0, r = 6, mid = 3, nums[mid] = 1
# 若 target = 6，左半边是无序的，则在 [l, mid - 1] 中查找。
# 若 target = 4，右半边是有序的，则在 [mid + 1, r] 中查找。
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        n = len(nums)
        l, r = 0, n - 1
        while l <= r:
            # 如果 [l, r] 是有序，二分查找
            # 如果 [l, r] 是无序的，则一分为二，一个为有序，一个为无序
            mid = r + ((l - r) >> 1)

            if nums[mid] == target:
                return mid
            
            # 对于 [l, r] 有序，则 nums[l] <= nums[mid] 必定成立，
            # 下列代码是二分查找的过程。
            # 对于 [l, r] 无序，则 nums[l] <= nums[mid] 可能成立
            # 下列代码是二分查找或者划分有序/无序区间的过程
            if nums[l] <= nums[mid]: # 左半边有序，在左半边里查找
                if nums[l] <= target < nums[mid]:   # 目标落在有序的左半边内
                    r = mid - 1 
                else: # 目标在无序半边内
                    l = mid + 1 
            else: # 右半边有序，在右半边内查找
                if nums[mid] < target <= nums[r]: # 目标落在有序的右半边内
                    l = mid + 1
                else: # 目标在无序半边内
                    r = mid - 1
        return -1  # 未查找到
