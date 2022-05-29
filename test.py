from queue import PriorityQueue

class Node:
    def __init__(self, val):
        self.val = val

    def __repr__(self):
        return "Node(val={})".format(self.val)

class ComparableNode(Node):
    def __lt__(self, other):
        return self.val < other.val

    # def __gt__(self, other):
    #     return self.val > other.val

    # def __eq__(self, other):
    #     return self.val == other.val

# 如果是负的，就自动从大到小
# 取出的时候再取反即可
aa = ComparableNode(3)
bb = ComparableNode(4)
cc = ComparableNode(4)
dd = ComparableNode(5)
p = PriorityQueue()
p.put(aa)
p.put(bb)
p.put(cc)
p.put(dd)

print(p.queue)
