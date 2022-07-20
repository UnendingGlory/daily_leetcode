# Definition for a binary tree node.
from tkinter.tix import Tree
from turtle import left
from typing import List

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Solution：先序遍历的第一个数总是根结点。
# 在中序遍历中找到该结点，然后再左右递归建树。
# 左子树为递归的左返回，右子树为递归的右返回。
# 先序序列 preorder：[3,9,20,15,7]
# 中序序列 inorder：[9,3,15,20,7]
# preorder第一个为3，在inorder中寻找 3。
# 9 为 3的左子树，15 20 7 为 3的右子树。
# 递归函数需要定义当前所在的先序和中序区间。
# 时间复杂度：O(n)，空间复杂度：O（n）
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        def constructTree(preL, preR, inL, inR):
            """[preL, preR]为先序，[inL, inR]为中序"""
            if preR < preL:
                return None
            root = TreeNode(preorder[preL])
            i = inL
            while i <= inR:
                if inorder[i] == preorder[preL]:
                    break
                i += 1
            left_len = i - inL
            root.left = constructTree(preL+1, preL+left_len, inL, i-1)
            root.right = constructTree(preL+left_len+1, preR, i+1, inR)
            return root
        return constructTree(0, len(preorder)-1, 0, len(inorder)-1)

# 时间复杂度优化。
# 针对 中序序列，提前建立好 结点值和下标之间的映射。
# 这样就避免了递归过程中的线性遍历寻找。
# 时间复杂度：O(n)，空间复杂度：O（n）
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        index = {element: i for i, element in enumerate(inorder)}
        def constructTree(preL, preR, inL, inR):
            """[preL, preR]为先序，[inL, inR]为中序"""
            if preR < preL:
                return None
            root = TreeNode(preorder[preL])
            i = index[preorder[preL]]
            left_len = i - inL
            root.left = constructTree(preL+1, preL+left_len, inL, i-1)
            root.right = constructTree(preL+left_len+1, preR, i+1, inR)
            return root
        return constructTree(0, len(preorder)-1, 0, len(inorder)-1)

