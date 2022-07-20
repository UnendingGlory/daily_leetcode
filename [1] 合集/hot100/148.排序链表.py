# 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表。

# 链表二分排序
# 二分方法：快慢指针，找到链表的中点。
# 二分到底后，使用 Merge 将两个有序链表合并即可。
# 归并：O(nlogn)
from typing import Optional


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def merge(self, head1, head2): # 合并两个有序链表到 head1 上
        l1, l2 = head1, head2
        p = dummy = ListNode(0)
        while l1 and l2:
            if l1.val < l2.val:
                p.next = l1
                l1 = l1.next
            else:
                p.next = l2
                l2 = l2.next
            p = p.next
        p.next = l1 if l1 else l2
        return dummy.next

    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
         # termination, 注意，这里需要判断 head.next
        if not head or not head.next:
            return head
        # 快慢指针法，快指针到尾部时，慢指针在中点
        fast, slow = head, head
        while True:
            if not fast.next or not fast.next.next:
                break
            fast = fast.next.next
            slow = slow.next
        # 此时slow到达中点

        mid = slow.next
        slow.next = None
        left = self.sortList(head) # sort半边
        right = self.sortList(mid)
        merged = self.merge(left, right); # 将排序好的两边 merge
        return merged
