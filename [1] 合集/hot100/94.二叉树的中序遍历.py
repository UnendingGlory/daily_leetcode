# Definition for a binary tree node.
from typing import Optional, List

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Solution1: 递归中序遍历。
# 时间复杂度: O(n)
class Solution:
    # Optional[TreeNode] 表示 root 既可以是 TreeNode类型，也可以是 None
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        ans = []
        def inorder(root):
            if root is None:
                return
            inorder(root.left)
            ans.append(root.val)
            inorder(root.right)
        inorder(root)
        return ans

# Solution2: 非递归中序遍历。
# 对于结点root，借助栈，先沿其左子树走到底并入栈。
# 再从栈中取一个元素，如果有右子树，直接将右子树赋给 root。
# 进入下一个循环。
# 时间复杂度：O(n)
class Solution:
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        stack, ans = [], []
        while len(stack) or root:
            while root:
                stack.append(root)
                root = root.left
            root = stack[-1]
            stack.pop()
            ans.append(root.val)
            root = root.right
        return ans
