# 判断nums中是否存在三个元素a, b, c。
# a + b + c = 0。
# 请你找出所有和为0且不重复的三元组。

# 注意，需要不重复。
# 对于原数组[-2, 1, -2, 1, 3]。
# 如果使用三重循环，[-2, 1, 1] 和 [1, -2, 1] 均是重复答案。
# 因此还需要哈希表对答案去重。
# 时间复杂度：O(N^3)，空间复杂度极高。

# 优化：不重复的本质是什么？
# 保持三重循环的框架不变，只需要保证枚举到的三元组(a, b, c)，满足 a <= b <= c
# 这样就可以有效减少重复，所以需要先对数组进行排序。

# 此外，对于每一重循环而言，相邻两次枚举的元素不能相同，否则也会造成重复。
# [-2, -2, 1, 1, 3]。
# 枚举第一个 -2 和 第二个 -2 会造成重复。
# 重复的话直接跳过该次枚举。
# 时间复杂度：O(N^3)，空间复杂度：O(1)

# 如何跳出三重循环的大框架？
# 如果固定了前两重循环枚举到的元素 a 和 b，那么只有唯一的 c 满足 a + b + c = 0
# 当第二重循环 b 往后枚举一个元素 b' 时，b' > b
# 那么满足 a + b' + c' = 0 的 c' 一定有 c' < c
# 所以说，其实对于每一个第二重循环的元素，不需要都有第三重循环。
# 只需要在第二重循环开始的时候，定义一个第三层循环的指针。
# 如果 first + second + third > 0
# 该指针从右到左一直移动即可。

# 总结：先对数组排序，然后固定一个数a，然后双指针 b、c 从两边从中间靠。
from typing import List
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        nums.sort()
        ans = list()
        # 枚举a
        for first in range(n):
            # 保证和上一次枚举的数不相同
            if first == 0 or nums[first] != nums[first-1]:

                third = n - 1 # 第三层循环的指针     
                for second in range(first+1, n):
                    if second == first + 1 or nums[second] != nums[second-1]:
                        while third > second and nums[first] + nums[second] + nums[third] > 0:
                            third -= 1
                        if third > second and nums[first] + nums[second] + nums[third] == 0:
                            ans.append([nums[first], nums[second], nums[third]])
        return ans

# 代码优化
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        nums.sort()
        ans = list()
        for first in range(n):
            if first > 0 and nums[first] == nums[first-1]:
                continue
            third = n - 1
            target = -nums[first]
            for second in range(first+1, n):
                if second > first + 1 and nums[second] == nums[second-1]:
                    continue
                while second < third and nums[second] + nums[third] > target:
                    third -=1
                if second == third: # 特殊情况判断
                    break
                if nums[second] + nums[third] == target:
                    ans.append([nums[first], nums[second], nums[third]])
        return ans
