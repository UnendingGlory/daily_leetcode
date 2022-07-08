# 给定一个 m x n 二维字符网格 board 和一个字符串单词 word。如果 word 存在于网格中，返回 true；否则，返回 false。
from typing import List

# 递归 + 回溯。
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        directions = [(1, 0), (0, 1), (0, -1), (-1, 0)] # 四个方向
        m, n = len(board), len(board[0])
        visited = [[False] * n for _ in range(m)]
        
        def dfs(i, j, ptr): # 遍历位置 (i, j), 指向 word 的 ptr
            if board[i][j] != word[ptr]:
                return False

            if ptr == len(word) - 1:
                return True

            visited[i][j] = True
            flag = False
            for d in directions:
                new_i, new_j = i + d[0], j + d[1]
                if new_i >= 0 and new_i < m and new_j >= 0 and new_j < n:
                    # 判断是否访问过
                    if not visited[new_i][new_j] and dfs(new_i, new_j, ptr+1):
                        flag = True
                        break
            visited[i][j] = False # 要重置访问位

            return flag

        for i in range(m):
            for j in range(n):
                if dfs(i, j, 0):
                    return True
        return False
