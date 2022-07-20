# 设计一个支持 push, pop, top 操作，并能在常数时间内检索到最小元素的栈。

# Solution: 在维护原栈的同时，维护一个同步大小的最小单调栈即可。
# 注意，题目保证了非空栈上操作
class MinStack:

    def __init__(self):
        # min_s 塞入最大值防止越界
        self.s, self.min_s = [], [float('inf')]

    def push(self, val: int) -> None:
        self.s.append(val)
        self.min_s.append(min(val, self.min_s[-1]))

    def pop(self) -> None:
        self.s.pop()
        self.min_s.pop()

    def top(self) -> int:
        return self.s[-1]

    def getMin(self) -> int:
        return self.min_s[-1]
