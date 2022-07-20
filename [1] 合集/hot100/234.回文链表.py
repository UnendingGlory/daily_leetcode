# Solution1：将值复制到数组中后，双指针判断。

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        p = head
        vals = []
        while p:
            vals.append(p.val)
            p = p.next
        i, j = 0, len(vals)-1
        while i < j:
            if vals[i] != vals[j]:
                return False
            i += 1
            j -= 1
        return True


# Solution2：将链表后半段反转后，使用快慢指针进行判断。
# 找到中点将后半段反转也需要用快慢指针。
# 实现方法会改变原链表，如果需要就地，可以再反转后半段链表进行恢复。
# 时间复杂度：O(n)，空间复杂度：O(1)
class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        slow, fast = head, head
        # 这样 slow找到的是前半段链表的尾结点
        while True:
            if not fast.next or not fast.next.next:
                break
            fast = fast.next.next
            slow = slow.next
        
        second_half_head = slow.next # 后半段的头结点
        slow.next = None
        pre, cur = None, second_half_head
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        
        p, q = head, pre
        while p and q:
            if p.val != q.val:
                return False
            p = p.next
            q = q.next
        return True
