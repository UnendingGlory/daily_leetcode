# 给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。
from typing import List

# Solution1: 暴力算法。
# 枚举元素，作为矩阵左上角和右下角，再去查询每个矩阵是否符合。
# 时间复杂度：O(m^2 * n^2)，不可取。

# Solution2: 换角度思考，问题转换。
# 对于矩阵的每个元素，计算该元素同行左边的元素的个数，记为left[i][j]。
# 对于每一个元素 matrix[i][j]，若其为1，以其为矩阵右下角，该矩阵面积记为 area。
# 枚举 0 <= k <= i，矩阵的最大宽度就是 left[i][j], left[i-1][j], ..., 
# left[k-1][j], left[k][j] 中的最小值。
# area是 每个中间矩阵面积 tmp 的最大值。
# 如对于 left中某列 5 0 2 1，假设以 1 为矩阵右下角，向上走。
# ... 5 ...
# ... 1 ...
# ... 4 ...
# ... 2 ...
# 对于 1，height = 1，width = 2，tmp = 2            , area = 2
# 对于 2，height = 2，width = 2，tmp = min(4, 2) = 2, area = max(2, 2) = 2
# 对于 0，height = 3，width = 1，tmp = min(3, 2) = 3, area = max(3, 2) = 3
# 对于 5，height = 4，width = 1，tmp = min(2, 5) = 2, area = max(2, 3) = 3
# 最终答案即所有 area 的最大值。
# 时间复杂度：O(m^2 * n)
class Solution:
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        m, n = len(matrix), len(matrix[0])
        left = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == '1':
                    left[i][j] = left[i][j-1] + 1 if j else 1
        ans = 0
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == '0':
                    continue
                width = left[i][j]
                area = width
                for k in range(i-1, -1, -1):
                    width = min(width, left[k][j])
                    area = max(area, (i-k+1) * width)
                ans = max(ans, area)
        return ans

# Solution3：时间复杂度优化。
# 得到 left[i][j]后，即可以转换为 84题：柱状图中的最大矩形。
# 即对于每一列，求一次柱状图中的最大矩形面积即可。
# 84题思路：对于每一个元素 h，找出左边第一个小于h的下标 left，右边第一个小于h的下标 right
# 该元素最大的矩形面积 area = (right - left - 1) * h。
# 如何求得？使用单调递增栈，对于元素 h，将大于等于h的全部 pop出去。
# 得到的第一个小于 h的下标即 left。
# 而被pop的元素对应的 right 即 h的下标 i。
# 时间复杂度：O(mn)
class Solution:
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        m, n = len(matrix), len(matrix[0])
        left = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == '1':
                    left[i][j] = left[i][j-1] + 1 if j else 1
        ans = 0
        for j in range(n): # 对于每一列，求柱状图中最大的矩形面积
            stack = [] # 存储下标
            down, up = [-1] * m, [m] * m
            for i in range(m):
                while len(stack) and left[stack[-1]][j] >= left[i][j]:
                    up[stack[-1]] = i
                    stack.pop()
                if len(stack): # 若栈有值
                    down[i] = stack[-1]
                stack.append(i)
            area = 0
            for i in range(m):
                area = max(area, (up[i] - down[i] - 1) * left[i][j])
            ans = max(area, ans)
        return ans
