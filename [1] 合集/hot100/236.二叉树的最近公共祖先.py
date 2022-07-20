# 递归向下判断
# 递归边界：如果 root 为空 || root = p || root = q，返回 root。 
# 否则，记左孩子 root.left 对 p 和 q的最近公共结点 left。
# 记左孩子 root.right 对 p 和 q的最近公共结点 right。
# 有以下几种情况：
# 1. left 和 right 均为空，返回空。
# 2. left 和 right 均不为空，那么 p 和 q 分属两侧，返回 root。
# 3. left 为空，right 不为空，那么 p 和 q 均在 root.right子树里，且 p 和 q 的 LCA 为right。
#    返回 right。
# 4. left不为空，right为空，同理返回 left。

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        if root is None or root == p or root == q:
            return root
        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)
        if left is None:
            return right
        if right is None:
            return left
        return root
