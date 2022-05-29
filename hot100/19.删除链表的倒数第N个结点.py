from header import ListNode

# 要删除倒数第n个结点。
# 理论上：先遍历一遍链表，得到链表的长度 k。
# 再去遍历一遍链表，去删除第 k - n 个结点。

# 采用双指针，第一个指针 p 先走 n 步
# 再开辟一个指针 q 从表头开始和 p 一起往前走，
# 当 p 到达链表尾部的时候，q就到达了要删除结点的前一个结点
# 1 -> 2 -> 3 -> 4 -> 5, n = 2
  
# 1 -> 2 -> 3 -> 4 -> 5, n = 2
#           |
#           p

# 1 -> 2 -> 3 -> 4 -> 5, n = 2
#           |         |
#           q         p

# 所以要判断的是 p->next == None
class Solution:
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        p, q = head, head

        for _ in range(n):
            p = p.next
            if p == None:
                break
        
        if p == None:
            return head.next
        
        while p.next != None:
            p = p.next
            q = q.next
        
        # 删除 q 结点后面的一个结点
        # 如果删除的 n = k，那么需要做特殊判断
        r = q.next
        q.next = r.next
        return head


# 优化：定义一个哑结点
# p 从 head 开始走，q 从 dummy 开始走，这样就避免了特殊判空
# dummy -> 1 -> 2 -> 3 -> 4 -> 5, n = 2
  
# dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> None
#                    |
#                    p

# dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> None
#                    |               |
#                    q               p
class Solution:
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        dummy  = ListNode(0, head)
        p = head
        q = dummy
        for _ in range(n):
            p = p.next
        while p:
            p = p.next
            q = q.next
        q.next = q.next.next
        return dummy.next
