# 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
# 求在该柱状图中，能够勾勒出来的矩形的最大面积。
# 输入：[2, 1, 5, 6, 2, 3]
# 输出：10，即 [5, 6] 构成的 5 * 2
from typing import List

# Solution1: 暴力，每个位置对宽度进行枚举。
# 时间复杂度：O(n^2)
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        n = len(heights)
        ans = 0
        for left in range(n):
            height = heights[left] # 每个宽度对应的高度
            for right in range(left+1, n):
                height = min(height, heights[right])
                area = (right - left + 1) * height
                ans = max(area, ans)
        return ans

# Solution2: 暴力，对高度进行枚举。
# 即固定某一根柱子高度 h，去两边搜索，遇到高度小于 h 的柱子就停下。
# 左侧指针停下为left，右侧指针停下为right，那么面积就是 (right - left + 1) * h
# 时间复杂度：O(n^2)
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        n = len(heights)
        ans = 0
        for i in range(n):
            left, right = i, i
            while left - 1 >= 0 and heights[left-1] >= heights[i]:
                left -= 1
            while right + 1 < n and heights[right+1] >= heights[i]:
                right += 1
            area = (right - left + 1) * heights[i]
            ans = max(area, ans)
        return ans

# Solution3: 对于2进行优化。
# 本质上，即对于每个元素 h，寻找左边第一个小于h的元素的下标 left，和右边第一个小于h的元素的下标 right。
# area = (right - left - 1) * h

# 如何寻找左边第一个小于 h 的元素？该元素对应下标记为 left。
# 可以使用单调递增栈，栈中存的是下标，栈底到栈顶下标对应的元素严格递增。
# 从左到右遍历，当遍历到下标对应的元素尾 num 时，将栈中所有对应元素 大于等于num 的下标 pop出。
# 从栈中拿到的第一个 小于h 的下标即想得到的 left。
# 极端情况下，如果栈为空，那么左侧元素均大于等于h，可以认为 left = -1。

# 如何寻找右边第一个小于 h 的元素？该元素对应下标记为 right。
# 使用单调递增栈，栈底到栈顶下标对应的元素严格递增。
# 从左到右遍历，当遍历到下标对应的元素 num 时，将栈中所有对应元素 大于等于num 的下标 pop出。
# 从栈中拿到的第一个 小于h 的下标即想得到的 right。
# 极端情况下，如果栈为空，那么右侧元素均大于等于h，可以认为 right = n。

# 时间复杂度：两次遍历 O(n)，空间复杂度：O(n)
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        n = len(heights)
        stack = []
        left, right = [-1 for _ in range(n)], [n for _ in range(n)]
        for i in range(n): # 从左往右
            while len(stack) and heights[stack[-1]] >= heights[i]:
                stack.pop()
            if len(stack): # 栈不为空
                left[i] = stack[-1]
            stack.append(i)
        stack = []
        for i in range(n-1, -1, -1): # 从右往左
            while len(stack) and heights[stack[-1]] >= heights[i]:
                stack.pop()
            if len(stack): # 栈不为空
                right[i] = stack[-1]
            stack.append(i)
        ans = 0
        for i in range(n):
            area = (right[i] - left[i] - 1) * heights[i]
            ans = max(ans, area)
        return ans

# Solution4: 对于 3 进行优化，只使用一次遍历。
# 事实上，从左到右遍历，当遍历到下标对应的元素为 num 时，将栈中所有对应元素 大于等于num 的下标 pop出。
# 从栈中拿到的第一个 小于h 的下标即想得到的 left。
# 这个时候，其实 left 是之前所有 pop 出的元素的 右边的第一个小于h的元素对应的下标。
# 比如：单调栈 [0, 1, 3, 4]，对于刚来的元素2， 3 和 4被 pop出。
#      同时 3 和 4 右侧第一个小于自己的元素其实就是 2。
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        n = len(heights)
        left, right = [-1] * n, [n] * n
        stack = []
        for i in range(n):
            while len(stack) and heights[stack[-1]] >= heights[i]:
                right[stack[-1]] = i
                stack.pop()
            if len(stack):
                left[i] = stack[-1]
            stack.append(i)
        ans = 0
        for i in range(n):
            area = (right[i] - left[i] - 1) * heights[i]
            ans = max(ans, area)
        return ans
