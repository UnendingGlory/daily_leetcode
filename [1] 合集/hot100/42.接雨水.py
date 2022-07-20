from typing import List

# 对于每一个位置i
# 可以接纳的雨水量为 min(i左边最高的柱子, i右边最高的柱子) - height[i]

# Solution1：前后缀最值 dp
# 时间复杂度：O(n)，空间复杂度：O(n)
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        pre = [0 for _ in range(n)]
        post = [0 for _ in range(n)]
        pre[0] = height[0]
        post[n - 1] = height[n - 1]
        for i in range(1, n):
            pre[i] = max(pre[i-1], height[i])
        for i in range(n-2, -1, 1):
            post[i] = max(post[i+1], height[i])
        ans = 0
        for i in range(n):
            ans += max(post[i], pre[i]) - height[i]
        return ans


# Soltuion2：双指针优化空间复杂度
# 使用两个指针，指向左边挡板最大值 和 右边挡板最大值

# 左指针向右，右指针向左
# 若 height[left] >= height[right], 则 leftMax >= rightMax，取右边挡板，right--
# 若 height[left] < height[right]，则 leftMax < rightMax，取左边挡板，left++

# 若 height[left] >= height[right]，则必然有 leftMax > rightMax

class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        left, right = 0, n - 1
        leftMax, rightMax = height[0], height[n-1]
        ans = 0
        while left < right:
            leftMax = max(leftMax, height[left])
            rightMax = max(rightMax, height[right])
            if height[left] >= height[right]:
                ans += rightMax - height[right]
                right -= 1
            else:
                ans += leftMax - height[left]
                left += 1
        return ans


# Soltuion3：单调栈，栈底到栈顶递减。
# 栈中存储元素下标。
# [left, top], height[i]，left < top < height[i]
# 就会形成一个凹槽，宽度是 i - left - 1，高度为 min(left, height[i]) - top
# 可容纳水量为 min(left, height[i]) - top。
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        stk = []
        ans, i = 0, 0
        while i < n:
            # 比栈顶元素大，可以得到一个接雨水的区域
            while len(stk) and height[i] > height[stk[-1]]:
                top = stk[-1]
                stk.pop()
                
                if len(stk) == 0:
                    break

                # pop 完后栈顶是 left
                w = i - stk[-1] - 1
                h = min(stk[-1], height[i]) - top
                ans += w * h
            stk.append(i) # 这里 height[i] 比栈顶元素小，可以入栈了
            i += 1
        return ans
