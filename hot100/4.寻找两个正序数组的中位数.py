# 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
# 请你找出并返回这两个正序数组的 中位数 。
# 时间复杂度应该为 O(log(m+n))

# https://leetcode.cn/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/

# [1, 3] [2] --> 2.0000
# [1, 2] [3, 4] --> 2.5000

# 最简单的思路
# 1. 合并两个有序数组，之后直接返回大数组的中间位置元素即可。
#    合并的时间复杂度：O(m+n)，空间复杂度：O(m+n)。

# Solution1: 不合并，使用双指针指向两个数组的开头，然后小指针前移即可，一直到中间位置。
#    时间复杂度o(m+n)，空间复杂度：O(1)

# 如果数组长度和是奇数，那么就是第 (m + n + 1) / 2 个数，奇数只需要最后一次遍历的结果
# 如果数组长度和是偶数，那么就是第 (m + n) / 2 和 第 (m + n) / 2 + 1个数的平均
# 如果是奇数，(m + n + 1) / 2 = floor((m + n) / 2) + 1
# 偶数需要最后一次和上一次遍历的结果
# 均要遍历 floor((m + n) / 2) + 1 次

from turtle import right
from numpy import Infinity


class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        m, n = len(nums1), len(nums2)
        i, l, r, half = 0, 0, 0, (m + n) // 2
        last, cur = -1, -1

        while i <= half: # 遍历 half + 1 次
            cur = last
            if l < m and (r >= n or nums1[l] < nums2[r]): # 还要考虑nums1数组过长
                cur = nums1[l]
                l = l + 1
            else:
                cur = nums2[r]
                r = r + 1
            i += 1
        
        if ((m + n) & 1 == 0): # 长度和为偶数
            return (last + cur) / 2
        return cur


# Solution2: 如果有log的时间要求，应该能想到二分
# 可以转化成寻找两个有序数组中的第 k 小的数，其中 k 为 (m+n)/2 或 (m+n)/2 + 1
# Solution1中是一个个数字排除的，其实可以以 k / 2 为一块排除

# A: 1 2 3 6
# B: 1 3 4 5 9 10
# k = (4 + 6) / 2 = 5, 要比较的下标 k / 2 - 1 = 1

# A: 1 2 | 3 6
# B: 1 3 | 4 5 9 10

# 下标 1 指向的元素分别为 2 和 3
# 其中 2 < 3，2不可能是第5个小的数，所以排除 A 中的1, 2
# 再根据排除数的个数减少k的值

# 该算法总结：
# 1. 如果 A[k/2-1] < B[k/2-1], 则比 A[k/2-1]小的数最多只有
#    A的前k/2-1个数，和B的前k/2-1个数，最多k-2个数，因此A[0]到A[k/2-1]可以全部排除。
# 2. 同理，如果 A[k/2-1] > B[k/2-1]，B[0]到B[k/2-1]可以全部排除。
# 3. 如果 A[k/2-1] = B[k/2-1]，可以归纳进第一种情况。
# 时间复杂度：O(log(m + n))，空间复杂度：O(1)

# 注意有三种情况需要特殊处理。
# 1. 如果 A[k/2-1] 和 B[k/2-1]越界，那么可以选取对应数组的最后一个元素。
#    同时 k 需要减去排除数的个数，而不是正常情况下的 k / 2，合并为 k 减去排除数个数即可。
# 2. 如果一个数组为空，说明该数组中的所有元素都被排除，可以直接返回另一个数组中第 k 小的元素。
# 3. 如果 k = 1，我们返回两个数组首元素的最小值即可。


class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        def getKthElement(k):
            """
            - 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
            - 这里的 "/" 表示整除
            - nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
            - nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
            - 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
            - 这样 pivot 本身最大也只能是第 k-1 小的元素
            - 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
            - 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
            - 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
            """
            index1, index2 = 0, 0 # 当前下标
            while True:
                # 特殊情况
                if index1 >= m:
                    return nums2[index2 + k - 1]
                if index2 >= n:
                    return nums1[index1 + k - 1]
                if k == 1:
                    return min(nums1[index1], nums2[index2])
                
                # 正常情况，避免越界
                newIndex1 = min(index1 + k // 2 - 1, m - 1)
                newIndex2 = min(index2 + k // 2 - 1, n - 1)
                pivot1, pivot2 = nums1[newIndex1], nums2[newIndex2]
                if pivot1 <= pivot2: # 排除nums1中 newIndex1前的所有
                    k -= newIndex1 - index1 + 1
                    index1 = newIndex1 + 1
                else:
                    k -= newIndex2 - index2 + 1
                    index2 = newIndex2 + 1

        m, n = len(nums1), len(nums2)
        total = m + n
        if total & 1: # 奇数
            return getKthElement((total + 1) // 2)
        else:
            return (getKthElement(total // 2) + getKthElement((total // 2) + 1)) / 2


# Solution3: 更优秀的一种二分的做法。
# 首先，在任意位置 i 将 A 划分成两个部分 left_A 和 right_A。
# A: A[0], A[1], ..., A[i-1] | A[i], A[i+1], ..., A[m-1]
# 共有 m 种划分方法
# 采用同样的方式，在任意位置 j将 B 划分成两个部分 left_B 和 right_B：
# B: B[0], B[1], ..., B[j-1] | B[j], B[j+1], ..., B[n-1]
# 共有 n 种划分方法
# 将left_A 和 left_B 放入一个集合 left，right_A 和 right_B 放入一个集合 right
# 若 A 和 B 长度和为偶数，若总是可以确定
# 1. len(left) = len(right)
# 2. max(left) <= min(right)
# 那么，A 和 B 的中位数就是 (max(left) + min(right)) / 2
# 若 A 和 B的长度和为奇数，且
# 1. len(left) = len(right) + 1
# 2. max(left) <= min(right)
# 那么，A 和 B 的中位数就是 max(left)

# 要确保这两个条件，需要满足以下条件：
# m+n为偶数时，i + j = m - i + n - j      ===> i + j = (m + n) / 2 = (m + n + 1) / 2
# m+n为奇数时，i + j = m - i + n - j + 1  ===> i + j = (m + n + 1) / 2
# 1. 可以合并为 i + j = (m + n + 1) / 2, 0 <= i <= m, 0 <= j <= n
# 2. j = (m + n + 1) / 2 - i, 若 m > n, 那么 j 可能是负数
#    所以需要保证 m <= n
# 3. 由于 A 和 B 是有序的两个数组，所以需要保证
#    B[j-1] <= A[i] 且 A[i-1] <= B[j]

# 越界情况分析：可以假设，A[i-1], B[j-1], A[i], B[j] 始终存在
# 若 i = 0, A[-1]; j = 0, B[-1]; i = m, A[m]; j = n, B[n];
# 对于 A[-1], B[-1], A[m], B[n] 这样的临界情况，可以规定
# A[-1] = B[-1] = -inf
# A[m] = B[n] = inf
# 这样，条件 3 就可以直接满足

# 我们需要做的就是：
# 在 [0, m] 中找到 i，使得：B[j-1] <= A[i] 且 A[i-1] <= B[j]
# 其实等价于：
# 在 [0, m] 中找到 最大的i，使得： A[i-1] <= B[j]
# 1. i 递增时，A[i-1]递增， B[j]减小，所以一定存在一个最大的 i 使得：A[i-1] <= B[j]
#    其中 j = (m + n + 1) / 2 - i
# 2. 既然是最大的，那么 i' = i + 1个就不满足，即 A[i'-1] > B[j']
#    将 i' = i+1 带入，则有j' = (m + n + 1) / 2 - i' = j - 1
#    即 A[i] > B[j-1]

# 所以我们需要可以在 [0, m]区间上对 i进行二分搜索
# 找到最大的满足 A[i-1] <= B[j] 的 i即可
# 此时，划分前一部分元素中的最大值，以及划分后一部分元素中的最小值，才可能作为就是这两个数组的中位数。
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        if len(nums1) > len(nums2):  # 保证在短的数组上二分
            return self.findMedianSortedArrays(nums2, nums1)
        
        m, n = len(nums1), len(nums2)
        l, r = 0, m
         # python浮点数无穷大Inifinity，理论上可以无穷大整数
         # 所以预设为题目的范围
        infinity = 10**6 + 1

        left_max, right_min = 0, 0 # 前一部分最大值和后一部分最小值

        while l <= r:
            i = l + ((r - l) >> 1) # 二分i
            j = (m + n + 1) // 2 - i

            left_i = (-infinity if i == 0 else nums1[i-1]) # A[i-1]
            left_j = (-infinity if j == 0 else nums2[j-1]) # B[j-1]
            right_i = (infinity if i == m else nums1[i]) # A[j]
            right_j = (infinity if j == n else nums2[j]) # B[j]

            if left_i <= right_j:
                left_max = max(left_i, left_j)
                right_min = min(right_i, right_j)
                l = i + 1
            else:
                r = i - 1

        if ((m + n) & 1):
            return left_max
        else:
            return (left_max + right_min) / 2
