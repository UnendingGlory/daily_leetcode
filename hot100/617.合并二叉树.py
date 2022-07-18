# 如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，不为 null 的节点将直接作为新二叉树的节点。
# 返回合并后的二叉树。

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# 直接从两个根结点 node1 和 node2开始合并。
# 在 node1上就地合并（要先确定是否能对原树修改）。
# 如果 node1 或 node2 为空，返回该结点。
# 如果均不为空，结点值叠加。
class Solution:
    def mergeTrees(self, root1: TreeNode, root2: TreeNode) -> TreeNode:
        if root1 is None or root2 is None:
            return root1 or root2
        root1.val += root2.val
        root1.left = self.mergeTrees(root1.left, root2.left)
        root1.right = self.mergeTrees(root1.right, root2.right)
        return root1
