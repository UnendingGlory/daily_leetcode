from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None) -> None:
        self.val = val
        self.left = left
        self.right = right

# Solution：递归。
# dfs 判定两棵子树是否是对称的。
# dfs(node1, node2) 判断node1 和 node2 值是否相等。
# 再递归遍历 node1.left 和 node2.right,
# node1.right 和 node2.left 即可。
class Solution: 
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        def dfs(node1, node2):
            if not node1 and not node2:
                return True
            if not node1 or not node2:
                return False
            if node1.val != node2.val:
                return False
            return dfs(node1.left, node2.right) and dfs(node1.right, node2.left)
        return dfs(root.left, root.right)
