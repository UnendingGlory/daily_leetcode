from typing import List

# 计算岛屿数量，'0', '1'组成的图，计算连通 的1 的块数量

# Solution1：DFS
# 由于题目没有规定不可以修改原数组，因此我们可以：
# 当遍历到 '1' 的数字时，答案 + 1，然后将该位置 '1' 修改为 '0'。
# 并再对该位置进行 DFS，这样不需要额外判断，也不需要额外空间。
# 时间复杂度：O(mn)，空间复杂度：O(mn) 栈空间。
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        row = len(grid)
        if row == 0:
            return 0
        col = len(grid[0])
        d = [(1, 0), (0, 1), (-1, 0), (0, -1)]

        def dfs(i, j):
            grid[i][j] = '0' # 遍历到了1，将该位置修改为 0
            for k in d:
                new_i, new_j = i + k[0], j + k[1]
                if 0 <= new_i < row and 0 <= new_j < col and grid[new_i][new_j] == '1':
                    dfs(new_i, new_j)
        
        ans = 0
        for i in range(row):
            for j in range(col):
                if grid[i][j] == '1':
                    ans += 1
                    dfs(i, j)
        
        return ans

# Solution2：BFS，思路与 Solution1 类似，只是修改为了图的 BFS 算法。
# 如果某个结点为 '1'，那么对其进行 BFS，BFS时将为 '1' 的结点均修改为 '0'。
# 每次从队列中取出一个结点，然后将邻居结点打入队列中。
# python3 队列：collection.deque。
# 时间复杂度：O(mn)，空间复杂度：O(mn)，队列空间。
import collections
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        row = len(grid)
        if row == 0:
            return 0
        col = len(grid[0])
        d = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        
        def bfs(i, j):
            neighbours = collections.deque()
            neighbours.append((i, j))
            while neighbours:
                x, y = neighbours.popleft()
                grid[x][y] = '0'
                for k in d:
                    new_i, new_j = x + k[0], y + k[1]
                    if 0 <= new_i < row and 0 <= new_j < col and grid[new_i][new_j] == '1':
                        neighbours.append((new_i, new_j))
                        grid[new_i][new_j] = '0' # 小操作减少循环次数

        ans = 0
        for i in range(row):
            for j in range(col):
                if grid[i][j] == '1':
                    ans += 1
                    bfs(i, j)
        return ans

# Solution3: 并查集
# 扫描整个图，如果一个位置为1，那么将其与相邻四个方向上的1在并查集中合并。
# 最终结果就是并查集中连通分量的个数。
# 计算连通分量个数可以在并查集操作中顺便完成。
# 时间复杂度：O(mn)，空间复杂度：O(mn)
class UnionFindSet:
    def __init__(self, grid) -> None:
        row, col = len(grid), len(grid[0])
        self.father = [-1] * (row * col)
        self.count = 0 # 连通分图数量
        for i in range(row):
            for j in range(col):
                if grid[i][j] == '1':
                    # 使用列进行索引不会越界
                    self.father[i * col + j] = i * col + j
                    self.count += 1
    
    def find(self, x): # 路径压缩
        a = x
        while(x != self.father[x]):
            x = self.father[x]
        while a != self.father[a]:
            next = self.father[a]
            self.father[a] = x
            a = next
        return x
    
    def unoin(self, a, b):
        father_a, father_b = self.find(a), self.find(b)
        if father_a != father_b:
            self.father[father_a] = father_b
            self.count -= 1 # 每union一次，count--

    def getCount(self):
        return self.count

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        row = len(grid)
        if row == 0:
            return 0
        col = len(grid[0])
        d = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        ufs = UnionFindSet(grid=grid)
        for i in range(row):
            for j in range(col):
                if grid[i][j] == '1':
                    grid[i][j] = '0'
                    for k in d:
                        new_i, new_j = i + k[0], j + k[1]
                        if 0 <= new_i < row and 0 <= new_j < col and grid[new_i][new_j] == '1':
                            ufs.unoin(i * col + j, new_i * col + new_j) # 到结点编号的映射
        return ufs.getCount()
