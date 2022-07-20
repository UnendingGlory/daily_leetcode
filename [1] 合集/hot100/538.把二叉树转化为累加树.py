# 给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。
from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 二叉搜索树中，左子树比根结点的值小，右子树比根结点的值大。
# 所以对于某个结点 node，如果是右子结点，累加上右边所有结点的值。
#                     如果是左子结点，累加上父结点和父结点的所有右子结点的值。
# 所以需要采用 [右 根 左] 这样的遍历顺序。
# 然后到底部时，再向上递归。 


# Solution1：反中序遍历，采用一个全局变量累加即可。
# 时间复杂度：O(n)，空间复杂度：递归栈 O(n)。
class Solution:
    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        sum = 0
        def dfs(node):
            if node is None:
                return
            dfs(node.right)
            nonlocal sum
            sum += node.val
            node.val = sum
            dfs(node.left)
        dfs(root)
        return root


# Solution2：Morris反中序遍历。
# 二叉树遍历的核心问题：遍历完当前结点的左子树后，指针指向的位置为左子树的最右节点，
#                   如何返回当前结点并继续遍历当前结点的右子树。
# Morris遍历其实就是利用二叉树的空节点来完成该过程（遍历过程中伴随线索化、去线索化过程）。
# Morris遍历是一个迭代过程，假设当前遍历结点为 cur。
# 1. cur无左子树，cur = cur.right
# 2. cur有左子树，在原未修改的树中，先找到 cur左子树的最右边的结点 pre。
# ① 若 pre右指针为空，添加线索，pre.right = cur，cur = cur.left。
# ② 若 pre右指针不为空，去线索，pre.right = null，cur = cur.right（第二次遍历该结点了，往右走）。
# 结束迭代条件：cur = null
# 有左子树的结点会遍历 2次，没有左子树的结点遍历 1次。
# 注意细节处理，在找 cur左子树最右边结点时候的循环判断条件。
# 时间复杂度：O(n)，空间复杂度：O(1)。
class Morris:
    def inorder(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        ans = []
        cur = root
        while cur:
            if cur.left is None:
                ans.append(cur.val)
                cur = cur.right
            else:
                # 找到 cur左子树中最右边的结点 pre
                pre = pre.left
                while pre.right and pre.right != cur:
                    pre = pre.right
                if pre.right is None:
                    pre.right = cur
                    cur = cur.left
                else:
                    pre.right = None
                    # 中序遍历在这里加入答案
                    ans.append(cur.val)
                    cur = cur.right

# 反中序遍历的话左右颠倒即可。
class Solution:
    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        cur = root
        sum = 0
        while cur:
            if cur.right is None:
                sum += cur.val
                cur.val = sum
                cur = cur.left
            else:
                pre = cur.right
                while pre.left and pre.left != cur:
                    pre = pre.left
                if pre.left is None:
                    pre.left = cur
                    cur = cur.right
                else:
                    pre.left = None
                    sum += cur.val
                    cur.val = sum
                    cur = cur.left
        return root
