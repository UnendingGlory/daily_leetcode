from header import *
from typing import Optional
# 非空的链表，表示两个非负的整数。
# 每位数字都是按照逆序方式存储的。
# 返回一个表示和的链表

# 按照加法模拟即可
# 注意两个链表长短不一的问题
# case 1: 243 564 -> 708
# case 2: (注意是逆序存储)
# l1: 2 4 3
# l2: 1 2 3 4
#  l: 3 6 6 4

# case 3:
# l1: 1 2 3 4
# l2: 2 4 3
#  l: 3 6 6 4

# 就地操作，注意链接链表
# 就地更改
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        p, q, r = l1, l2, l1
        C, sum = 0, 0
        while p or q:
            if not p: # 如果p是空，则new一个结点
                p = ListNode(0)
                r.next = p
            sum = (p.val + q.val + C if q else p.val + C)
            C = sum // 10 # py里整除
            p.val = sum % 10
            r = p # 更新r
            if p:
                p = p.next
            if q:
                q = q.next
        if C: # 注意最后余下来的进位
            r.next = ListNode(C)
        return l1
