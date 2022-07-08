from typing import List
import collections
# 与 剑指offer39 相同

# Solution1: 哈希表
# 时间复杂度：O(n), 空间复杂度：O(n)
class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        n = len(nums)
        occur = collections.defaultdict(int)
        for num in nums:
            occur[num] += 1
            if occur[num] > n//2:
                return num
        # 将字典的键值对按照值从大到小进行排序
        # sorted_occur = sorted(occur.items(), key=lambda x: x[1], reverse=True)
        # ans = sorted_occur[0]


# Solution2: 快速排序后取中点
# 时间复杂度：O(nlogn), 空间复杂度：O(1)
# 使用sort，或者自己实现快排
# 该解法会超时
class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        def quickSort(l, r):
            if l >= r:
                return
            x, y, pivot = l, r, nums[l] # 双指针实现 patition
            while x < y:
                while x < y and nums[y] >= pivot: # 从后往前找寻比 pivot 小的
                    y -= 1
                nums[x], nums[y] = nums[y], nums[x]
                while x < y and nums[x] <= pivot: # 从前往后找寻比 pivot 大的
                    x += 1
                nums[x], nums[y] = nums[y], nums[x]
            # 最后, pivot 会归位到位置 x
            quickSort(l, x - 1)
            quickSort(x + 1, r)
        quickSort(0, len(nums)-1)
        return nums[len(nums) // 2]


# Solution3: 分治法
# 统计每个区间内出现次数最多的数。
# 递归求解子问题，如果区间中只有一个数 num，那么显然结果为 num。
# 否则，求解左半边区间出现次数最多的数 num1，再统计右边区间出现次数最多的数 num2，再进行合并。
# 如果 num1 == num2，则结果为 num1
# 如果 num1 != num2，则要统计两者在 *合并区间内* 的出现次数，取最大者。 
# 时间复杂度：O(nlogn), 空间复杂度：O(n)
class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        def countInRange(num1, num2, l, r):
            res1, res2 = 0, 0
            for i in range(l, r+1):
                if nums[i] == num1:
                    res1 += 1
                if nums[i] == num2:
                    res2 += 1
            return res1, res2
    
        def divide(l, r):
            if l == r:
                return nums[l]
            mid = l + ((r - l) >> 1)
            num1, num2 = divide(l, mid), divide(mid+1, r)
            if num1 == num2:
                return num1
            else:
                res1, res2 = countInRange(num1, num2, l, r)
                return num1 if res1 > res2 else num2
        return divide(0, len(nums)-1)

# Solution4: Moore投票法
# 时间复杂度：O(n), 空间复杂度：O(1)
# 维护一个候选人 candidate 和出现的次数count, candidate初始为 -1
# 遍历数组，对于每一个x，如果count = 0，则candidate = x
# count != 0时，若x == candidate，count++
# x != candidate，count--
class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        candidate, count = -1, 0
        for num in nums:
            if num == candidate:
                count += 1
            else:
                count -= 1
                if count < 0: # 重新挑选候选人，由于答案数字出现次数超过 n/2，结果必然正确
                    candidate = num
                    count = 1
        return candidate
