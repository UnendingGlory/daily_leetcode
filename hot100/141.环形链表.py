# 给定一个链表头结点 head，判断链表中是否有环。
from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

# Solution: 快慢指针
# 分析：快慢指针均从头结点开始。
# 假设从头结点到环的入口长度为 a，环的长度为 b
# 如果有环，会在某处相遇。
# 不能相遇，则不存在环。

class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        fast, slow = head, head
        while True:
            # 快指针能走到底，没有环
            if not fast or not fast.next:
                return False
            fast = fast.next.next
            slow = slow.next
            if fast == slow:
                break
        return True
