# get 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1。
# put 如果超出容量，应该逐出 最久未使用 的关键字。
# 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

# Solution：LRU 机制可以使用 哈希表 和 双向链表 实现。
# 1. 双向链表按照被使用的顺序存储了这些键值对，靠近头部的是最近使用，靠近尾部的是最久未使用的。
# 2. 实现快速索引，哈希表通过缓存数据的键，映射到其在双向链表中的位置。
class DListNode:
    def __init__(self, key=0, val=0) -> None:
        self.key = key
        self.val = val
        self.prev = None
        self.next = None


class LRUCache:
    def __init__(self, capacity: int):
        self.cache = dict()
        # 头结点和尾结点
        self.head = DListNode()
        self.tail = DListNode()
        self.head.next = self.tail
        self.tail.prev = self.head
        self.capacity  = capacity
        self.size = 0 # 记录当前链表大小

    def removeNode(self, node):
        # 删除某结点
        node.prev.next = node.next
        node.next.prev = node.prev

    def addToHead(self, node):
        # 将某结点添加到头结点
        node.prev = self.head
        node.next = self.head.next
        self.head.next.prev = node
        self.head.next = node

    def removeTail(self):
        # 将某结点从尾结点删除
        node = self.tail.prev
        node.prev.next = self.tail
        self.tail.prev = node.prev
        return node

    # 对于 get 操作，首先判断 key 是否存在。
    # 如果不存在，返回 -1。
    # 如果存在，则 key 对应的结点是最近使用过的结点，将该结点挪到链表头。
    def get(self, key: int) -> int:
        if not key in self.cache:
            return -1
        recent = self.cache[key]
        self.removeNode(recent)
        self.addToHead(recent)
        return recent.val

    # 对于 put 操作，首先判断 key 是否存在。
    # 如果存在，则变更其数据值 value， 并将该结点挪到头部。
    # 如果不存在，在链表头部添加该结点并查看 容量size。
    # 如果容量超出 capacity，那么将尾部的结点删除。
    # 并删除其在哈希表中对应的项。
    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            node = self.cache[key]
            node.val = value
            self.removeNode(node)
            self.addToHead(node)
            return
        node = DListNode(key, value)
        self.addToHead(node)
        self.cache[key] = node # 添加到哈希表中
        self.size += 1
        if self.size > self.capacity:
            removed = self.removeTail()
            self.cache.pop(removed.key) # 删除尾结点在哈希表中对应的项
            self.size -= 1


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
