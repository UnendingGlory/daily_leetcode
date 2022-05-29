import queue
from typing import List, Optional
from header import ListNode

# Solution1：利用 queue 中的 priorityQueue
# ListNode不能更改，但是需要对 pq 自定义比较方法
# 再自定义一个类
class ComparableNode:
    def __init__(self, node):
        self.node = node
        
    def __lt__(self, other):
        return self.node.val < other.node.val

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        pq = queue.PriorityQueue()

        # 先将每组第一个打入优先级队列
        for node in lists:
            if node:  # 输入中也可能存在空节点
                pq.put(ComparableNode(node))

        head = ListNode()
        p = head

        while not pq.empty():
            p.next = pq.get().node
            p = p.next
            if p.next: # 若放出来的结点后还有结点
                pq.put(ComparableNode(p.next)) # 将该结点放入队列

        return head.next


# Solution2：优先级队列基于堆，因此直接用 heapq 堆库
class ComparableNode:
    def __init__(self, node):
        self.node = node
        
    def __lt__(self, other):
        return self.node.val < other.node.val

class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        import heapq #调用堆
        minHeap = []
        for node in lists:
            if node:
                heapq.heappush(minHeap, ComparableNode(node)) #把listi中的数据逐个加到堆中
        dummy = ListNode(0)
        p = dummy
        while minHeap:
            p.next = heapq.heappop(minHeap).node #依次弹出最小堆的数据
            p = p.next
            if p.next:
                heapq.heappush(minHeap, ComparableNode(p.next))
        return dummy.next       


# Solution2 中构建中间对象较为耗时
# Solution3：直接用值构造
class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        import heapq #调用堆
        minHeap = []
        for listi in lists: 
            while listi:
                heapq.heappush(minHeap, listi.val) #把listi中的数据逐个加到堆中
                listi = listi.next
        dummy = ListNode(0) #构造虚节点
        p = dummy
        while minHeap:
            p.next = ListNode(heapq.heappop(minHeap)) #依次弹出最小堆的数据
            p = p.next
        return dummy.next   
