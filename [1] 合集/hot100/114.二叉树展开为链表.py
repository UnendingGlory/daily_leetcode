# Definition for a binary tree node.

# 展开后的单链表应该同样使用 TreeNode，其中right子指针指向链表中下一个结点，而左子指针始终为null。
# 展开后的单链表应该与二叉树 先序遍历 顺序相同。

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Solution1：先获得先序遍历结点序列，再去修改这些结点序列
class Solution:
    def flatten(self, root: TreeNode) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        preOrderList = []
        def preOrderTraverse(node):
            if not node:
                return
            preOrderList.append(node)
            preOrderTraverse(node.left)
            preOrderTraverse(node.right)

        preOrderTraverse(root)

        for i in range(1, len(preOrderList)):
            prev, cur = preOrderList[i-1], preOrderList[i]
            prev.left = None
            prev.right = cur

# Solution2: 就地修改。
# 回顾 Morris 遍历，原理与其类似。
# 就地的诀窍在于不使用栈等结构，遍历完左子树后，返回当前结点。
# 对于结点 root，访问 root左子树 最右的结点 pre。
# 将 pre的 right 赋值为 root.right。
# 注意，pre不一定是root的前驱结点。
# 特殊情况：结点均没有右子树，均只有左子树，但是这种解法也正确。
class Solution:
    def flatten(self, root: TreeNode) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        cur = root
        while cur:
            if cur.left:
                prev = nxt = cur.left
                while prev.right:
                    prev = prev.right
                prev.right = cur.right
                cur.left = None 
                cur.right = nxt # 将原结点左子树赋为原子树
            cur = cur.right
        