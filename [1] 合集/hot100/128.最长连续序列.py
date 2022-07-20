# 给定一个未排序的整数数组 nums，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
# 输入：[100, 4, 200, 1, 3, 2]
# 输出：[4, 1, 3, 2] -> 4
# 实现时间复杂度为 O(n) 的算法解决此问题
import faulthandler
from gettext import find
from typing import List, Union


# Solution1: 暴力算法。
# 对于每个元素 x，检查 x + 1, x + 2 ... x + n 是否在数组中。
# 检查采用哈希表的方式。过程中更新答案。
# 时间复杂度：O(n^2)
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        occur = {num: True for num in nums}
        n, ans = len(nums), 0
        for x in nums:
            l = 0
            for i in range(n):
                if x + i in occur:
                    l += 1
            ans = max(ans, l)
        return ans


# Solution2：时间复杂度优化。
# 有很多不必要的枚举，如果已知检查过一个 x, x+1, x+2 ..., x+y的连续序列。
# 对于另一个数y，却重新从 x+1, x+2 或者 x+y 处开始匹配，
# 那么结果肯定不会优于枚举 x为起点的答案。
# 那么怎么判断是否跳过呢？
# 我们将枚举到的数使用一个 set 记录下来。
# 由于我们要枚举的数 x 一定是在数组中不存在前驱数 x-1 的。
# 我们每次在哈希表中检查是否存在 x-1 即能判断是否需要跳过了。
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        longest_streak = 0
        occur = set(nums)
        for num in nums:
            if num - 1 not in occur:
                cur_num = num
                streak = 1
                while cur_num + 1 in occur:
                    cur_num += 1
                    streak += 1

                longest_streak = max(longest_streak, streak)
        return longest_streak


# Solution3：并查集。
# 如果 num - 1 或者 nums + 1在map中，
# 就将 num[i]结点 和 num[i] - 1结点 或者 num[i] + 1 结点相连。
# 然后得到多个连通子图，返回结点数最多的连通子图的结点数。
class UnionFindSet:
    def __init__(self, length) -> None:
        self.length = length
        self.father = [i for i in range(length)]
        # 以 i 为根的子图的结点数
        self.size = [1 for _ in range(length)]
    
    def find(self, x):
        '''寻找x的父结点并进行路径压缩'''
        z = x
        while x != self.father[x]:
            x = self.father[x]
        while z != self.father[z]:
            y = self.father[z]
            self.father[z] = x
            z = y
        return x
    
    def union(self, a, b):
        father_a, father_b = self.find(a), self.find(b)
        if father_a != father_b:
            self.father[father_a] = father_b
            self.size[father_b] += self.size[father_a]
    
    def getMaxGraphSize(self):
        '''返回结点数最多的连通子图的结点数'''
        maxSize = 0
        for i in range(self.length):
            if i == self.father[i]: # 根结点
                maxSize = max(maxSize, self.size[i])
        return maxSize


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        n = len(nums)
        ufs = UnionFindSet(n)
        occur = {}
        for i in range(n):
            if nums[i] in occur: # 重复元素则跳过 
                continue
            if nums[i] - 1 in occur:
                ufs.union(i, occur[nums[i]-1])
            if nums[i] + 1 in occur:
                ufs.union(i, occur[nums[i]+1])
            occur[nums[i]] = i
        return ufs.getMaxGraphSize()
