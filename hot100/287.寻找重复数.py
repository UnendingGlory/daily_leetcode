# 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），
# 可知至少存在一个重复的整数。返回这个重复的数。
# 必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。
# 如果可以使用O(n)的空间，那么可以使用哈希表。 

# Solution1：索引排序法。
# 如果可以进行就地修改，那么可以利用性质进行交换判断。
# 如果无重复元素，排序后，nums[i]应该被安放在 nums[i]-1 的位置。
# 可以对原数组进行遍历，对于数组中每个nums[i]，作为索引。
# 1. 如果 nums[i] == i + 1，说明该位置已经排序好。
# 2. 如果 nums[i] == nums[nums[i]-1]，那么说明遇到了重复数字，返回nums[i]。
# 3. 否则，swap(nums[i], nums[nums[i]-1])。
# 时间复杂度：O(n)，空间复杂度：O(1)
from typing import List
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        n = len(nums)
        i = 0
        while i < n:
            x = nums[i]
            if x == i + 1:
                i += 1
                continue
            if x == nums[x-1]:
                return x
            else:
                nums[i] = nums[x-1]
                nums[x-1] = x
        return -1


# Solution2：小于等于的计数序列上二分。
# 由于不能修改原数组，因此需要想其他办法。
# 使用 cnt[i] 来表示 <= i 的个数。
# i 从 1 到 n，那么 cnt[i] 必定是递增数列。
# 对于重复元素 target，必定有以下性质：
# i 属于 [0, target-1]，那么 cnt[i] <= i。
# i 属于 [target, n]，那么 cnt[i] > i。
# 所以我们需要在 cnt[i]中找到第一个满足条件 cnt[i] > i 的元素。
# 在实际的编码中，cnt[i]不需要存储，使用一个变量在二分时统计即可。
# 时间复杂度：O(nlogn)，空间复杂度：O(1)
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        l, r = 1, len(nums) - 1 # nums 长度为 n+1，搜索范围为 [1, n]
        ans = -1
        while l <= r:
            mid = l + ((r - l) >> 1)
            # 统计 <= mid 的元素个数
            cnt = 0
            for num in nums:
                cnt += (num <= mid)
            if cnt <= mid:
                l = mid + 1
            else:
                ans = mid
                r = mid - 1
        return ans


# Solution3：二进制。
# 对于 nums数组 和 [1...n] 数组，统计 x 和 y。
# x为 nums   数组中的元素按照二进制位展开后，第 i位为 1的元素个数。
# y为 [1..n] 数组中的元素按照二进制位展开后，第 i位为 1的元素个数。
# 如果 x > y，那么重复的数的第 i位就为 1，否则重复数的第 i位为 0。
# i 为从 0 到 n的位数。
# 时间复杂度：O(n)，时间复杂度：O(1)
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        # 首先统计 n的位数。
        bits, n = 0, len(nums) - 1
        while n:
            n >>= 1
            bits += 1
        ans = 0
        for i in range(bits+1):
            x, y = 0, 0
            for j in range(len(nums)): # [0-n]
                if nums[j] & (1 << i):
                    x += 1
                if j >= 1 and (j & (1 << i)):
                    y += 1
            if x > y:
                ans = ans | (1 << i)
        return ans

# Solution4：快慢指针判圈法。
# 对 nums进行建链表，建立 i -> nums[i] 的边。
# 由于数组存在重复元素，假设为 target，那么一定会有两个元素 x, y 指向target。
# 同时 target会指向另一个元素 z，z通过链路会指回 x 和 y。
# 所以图中一定存在环，且环的入口为 target。
# 所以转换为链表中环的入口结点问题，使用快慢指针。
# 由于数组中的元素均在 [1, n] 之间，且数组长度为n，可以将题目给的数组当成一个静态链表看待。
# 由于元素在[1, n]之间，所以没有元素指向0，即链表头 0。

# 快慢指针 slow 和 fast，最终会在环内的某个结点相遇。
# 假设表头到环的入口结点长度为 a，环的长度为 b。
# 假设 slow走了 s步，fast 走了 f步。
# 则有 f = 2s，f = s + Nb => s = Nb。
# 即慢指针走的长度为环的整数倍。
# 再思考一个问题，假设一个指针走了 a + mb步，那么必定会到达环的入口结点。
# 慢指针走a步即可到达入口结点。
# 定义一个指针从头开始，和慢指针同时走，最后必定会在环的入口结点相遇。

# 假设为 [2, 2, 3, 1], 那么建图：
# 0 -> 2, 1 -> 2, 2 -> 3, 3 -> 1。
# 时间复杂度：O(n)，空间复杂度：O(1)
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        slow, fast = 0, 0
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                break
        fast = 0
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        return slow
