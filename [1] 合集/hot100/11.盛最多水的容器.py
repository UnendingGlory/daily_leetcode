# 给定一个长度为n的数组height。
# 找出其中的两条线，使得他们与x轴构成的容器可以容纳更多的水。

# 设两个指针 i，j；指向的水槽板高度为 h[i], h[j]；容纳水的面积为 S(i, j)
# 可容纳水的高度是由两板中的短板决定的。
# S(i, j) = min(h[i], h[j]) * (j - i)

# 每个状态下，无论长板或者短板向内收一格，水槽的底部都会 -1，变短
# 1. 若向内移动短板，水槽的短板 min(h[i], h[j]) 可能变大，S(i, j)也可能增大
# 2. 若向内移动长板，水槽的短板 min(h[i], h[j]) 不变或变小，S(i, j)一定减小

# 因此使用双指针，每次短板一直向内移动即可。
# 中间使用变量存储每次的面积值。
# 时间复杂度: O(N)

class Solution:
    def maxArea(self, height: List[int]) -> int:
        i, j, res = 0, len(height) - 1, 0
        while i < j:
            shorter = min(height[i], height[j])
            res = max(res, shorter * (j - i))
            if shorter == height[i]:
                i = i + 1
            else:
                j = j - 1
        return res
