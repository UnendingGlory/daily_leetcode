from typing import Optional
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 检查一棵二叉树是否是二叉搜索树

# Solution1：二叉搜索树的性质，左边子树均比当前结点值小，右边子树均比当前结点值大。
# 所以递归时需要判断 当前结点值是否在 [lower, upper] 范围内
# 如果遍历左子树，那么 upper 就设置为 node.val
# 如果遍历右子树，那么 lower 就设置为 node.val
# 从上往下递归
class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def dfs(node, lower, upper):
            if not node: # 空节点返回 True
                return True
            if lower < node.val < upper: # 如果在范围内
                return dfs(node.left, lower, node.val) and dfs(node.right, node.val, upper)
            return False

        return dfs(root, -float('inf'), float('inf'))

# Solution2：利用二叉搜索树的性质，二叉搜索树的中序遍历序列是递增的
# 所以可以在中序遍历时检查是否递增即可。
# 递归版。
class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        pre = -float('inf')
        def dfs(node):
            nonlocal pre
            if not node:
                return True
            flag1 = dfs(node.left)
            if pre >= node.val:
                return False
            pre = node.val
            flag2 = dfs(node.right)
            return flag1 and flag2
        return dfs(root)

# Solution3：递归版
class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        pre = -float('inf')
        stack = []
        while len(stack) or root:
            while root:
                stack.append(root)
                root = root.left
            root = stack[-1]
            stack.pop()
            if root.val <= pre:
                return False
            pre = root.val
            root = root.right
        return True