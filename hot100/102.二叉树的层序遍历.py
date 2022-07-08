import collections
from typing import List
# Definition for a binary tree node.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Solution1：二叉树的层序遍历，使用队列结构。
# 每一层的个数即全部入栈后队列的大小。
# 优先使用内置collections，速度较快。
class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if not root:
            return []
        q = collections.deque()
        q.append(root)
        ans = []
        while q:
            level = []
            for _ in range(len(q)):
                node = q.popleft()
                level.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            ans.append(level)
        return ans

# Python使用两个列表来模拟队列，更快。
class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if not root:
            return []
        cur, next = [root], [] # 当前层和下一层
        ans = []
        while cur or next:
            level = []
            for node in cur:
                level.append(node.val)
                if node.left:
                    next.append(node.left)
                if node.right:
                    next.append(node.right)
            ans.append(level)
            cur, next = next, [] # 下一层清空
        return ans

# Solution2: 深度优先遍历，对于每一个结点都存储高度。
# 采用先序遍历，先入左子树，再入右子树，这样会得到正确的顺序。 
class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if not root:
            return []
        ans = []
        def dfs(node, h): # h: 当前结点的高度
            if not node:
                return
            if len(ans) <= h:
                ans.append([])
            ans[h].append(node.val) # 当前层打入
            dfs(node.left, h+1)
            dfs(node.right, h+1)
        dfs(root, 0)
        return ans