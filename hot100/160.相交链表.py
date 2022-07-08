# 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。
# 如果两个链表不存在相交节点，返回 null 。

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


# Solution: 假设 headA 不相交段的长度为 a，headB 不相交段的长度为 b，
# 相交段的长度为c。
# 那么设两个指针 p 和 q 同步向前走。
# p 从 headA 开始走，走到底再换 headB 开始走。
# q 从 headB 开始走，走到底再换 headA 开始走。
# 那么 p 和 q 相交的点，两者刚好都走了 a + b + c。
# 此时 p 就在 相交点处。

class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        p, q = headA, headB
        # 注意如果两个链表不相交，那么两个指针分别走了 a + b 步之后，
        # p 和 q 都是在表尾，为None，即相遇在空指针处。
        # 所以这里的判断条件一定是 p 是否为空。
        while p != q:
            p = p.next if p else headB
            q = q.next if q else headA
        return p
