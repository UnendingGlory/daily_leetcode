from typing import List
# 给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums，原地对它们进行排序，
# 使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
# 我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
# 注意，必须在不使用库的sort函数的情况下解决这个问题，且需要就地。

# Solution1: 计数，统计0, 1, 2的个数，然后覆盖原数组
# 时间复杂度：O(n)
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        nums0, nums1, nums2 = 0, 0, 0
        for num in nums:
            if num == 0:
                nums0 += 1
            if num == 1:
                nums1 += 1
            if num == 2:
                nums2 += 1
        idx = 0
        for _ in range(nums0):
            nums[idx] = 0
            idx += 1
        for _ in range(nums1):
            nums[idx] = 1
            idx += 1
        for _ in range(nums2):
            nums[idx] = 1
            idx += 1

# Solution2: 就地单指针。
# 时间复杂度：O(n)
# ptr = 0
# 第一趟遍历数组，如果遇到了 0 则交换之，并++ptr。
# 第二趟遍历数组，如果遇到了 1 则交换之，并++ptr。
# 最终数组中 0， 1， 2依次分块排布。
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        ptr = 0
        for i in range(n):
            if nums[i] == 0:
                nums[i], nums[ptr] = nums[ptr], nums[i]
                ptr += 1
        for i in range(n):
            if nums[i] == 1:
                nums[i], nums[ptr] = nums[ptr], nums[i]
                ptr += 1

# Solution3: 就地双指针。
# 时间复杂度：O(n)
# 双指针只需要一次遍历。
# 使用两个指针 p 和 q，分别用来交换 0 和 2。
# p负责将 0 交换到数组的头部，q负责将 2 交换到数组的尾部。
# 注意，如果 q 换出来的数字不是 1，则指针 i 需要回退。
# 例如对于数组 [0 2 1 0 0 2]
# i = 0, p = 0, q = 4, swap(nums[0], nums[p]), ++p, p = 1, [0 2 1 0 0 2]
# i = 1, p = 1, q = 4, swap(nums[1], nums[q]), --q, q = 3, [0 2 1 0 0 2]
# 注意，此时交换过来的 2 没有到数组的末尾，i不能再前进，需要保持 i = 1
# i = 1, p = 1, q = 3, swap(nums[1], nums[3]), --q, q = 2, [0 0 1 0 2 2]

# 例如对于数组 [1 2 0]
# i = 0, p = 0, q = 2, ++i
# i = 1, p = 0, q = 2, swap(nums[1], nums[q]), --q, q = 1, [1, 0, 2]
# 此时交换过来的是 0，而 0 没有放到数组的头部，因此 i 不能再前进，也需要保持 i = 1。
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        i, p, q = 0, 0, n - 1
        while i <= q:
            if nums[i] == 0:
                nums[i], nums[p] = nums[p], nums[i]
                p += 1
            if nums[i] == 2:
                nums[i], nums[q] = nums[q], nums[i]
                q -= 1
                if nums[i] != 1:
                    i -= 1


# 其他想到的Solution：并查集，下标为一个非连通图组。
# 但由于本题中只允许就地更改，不可行。
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        father = [i for i in range(n)]

        def find(x): # 查找 下标x 的根
            z = x
            while x != father[x]: # 循着路径查找根结点
                x = father[x]
            # 这里 x 已经是根节点
            # 路径压缩，将长的路径缩短，所有结点的父结点直接指向根结点
            while z != father[z]:
                y = father[z]
                father[z] = x
                z = y
            return x

        def union(a, b):
            father_a, father_b = find(a), find(b)
            if father_a != father_b:
                father[father_a] = father_b

        for i in range(1, n):
            if nums[i] == nums[i-1]:
                union(i, i-1)

        # union之后，每组的根节点满足条件：father[i] = i，查找即可
        ...
