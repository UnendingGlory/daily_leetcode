# 二叉树中从任意结点出发，到达另外某一节点的最大路径和。
# 结点不能重复遍历，类似图中的最大路径问题。
from typing import Optional
# Solution：递归。
#    a     
#  /  \
# b   c
# 对于根结点a，可能的路径情况：
# 1. b + a
# 2. c + a
# 3. b + a + c
# 递归写法：
# 对于某个结点 a，记录其左右子结点最大和 left 和 right。
# 若 left > 0，则计算 left_val = a.val + left
# 若right > 0，则计算right_val = a.val + right
# a的最大结点和则为 val = left_val + a.val + right_val
# 答案 res = max(res, val)
# 时间复杂度：O(n)


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def __init__(self) -> None:
        self.res = -float("inf")

    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        def maxSum(node):
            if not node:
                return 0
            left, right = maxSum(node.left), maxSum(node.right)
            left_val = left if left > 0 else 0
            right_val = right if right > 0 else 0
            val = left_val + right_val + node.val
            self.res = max(self.res, val)
            # 返回该结点对上面的最大贡献值
            return node.val + max(left_val, right_val)

        maxSum(root)
        return self.res
