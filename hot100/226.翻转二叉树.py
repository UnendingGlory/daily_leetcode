# 镜像翻转一棵二叉树

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# dfs，输入为一个结点 node。
# 如果 node 的两个子结点均不为空，那么交换之（指针层面的交换）。
# 直接递归交换即可。
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        def dfs(node):
            if node is None:
                return
            node.left, node.right = node.right, node.left
            dfs(node.left)
            dfs(node.right)
        dfs(root)
        return root
            