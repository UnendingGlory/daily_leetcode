# 给定一个链表头结点 head，返回链表入环的第一个结点。

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
# 假设 快指针 走了 c步，慢指针走了 d步。
# 则有 c = 2d, c = d + nb (快指针比慢指针多走 n 环)
# 推导出 d = nb;
# 即慢指针均走了环的整数倍。

# 此时，再考虑一个问题，如果某个指针走了 a + mb 步，
# 那么该指针必定会到达入口结点。
# 因此，只需要让慢指针再走 a 步即可。
# 只需要再定义一个指针从头开始和慢指针一起走，
# 相遇处即是环的入口结点。

class Solution:
    def detectCycle(self, head: ListNode) -> ListNode:
        fast, slow = head, head
        while True:
            # 快指针能走到底，没有环
            if not fast or not fast.next:
                return None
            fast = fast.next.next
            slow = slow.next
            if fast == slow:
                break

        fast = head # 重定义一个指针
        while fast != slow:
            fast = fast.next
            slow = slow.next
        return slow
