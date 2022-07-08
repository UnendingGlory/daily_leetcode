# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# 链表就地逆转
class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        # 从头结点开始，不需要 dummy 结点
        pre, cur = None, head 
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre
