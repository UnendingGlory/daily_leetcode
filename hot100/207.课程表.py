from typing import List
# 修课程顺序问题，经典拓扑排序。
# 即判断一个有向图中是否有环即可。

# 首先需要先建图，然后统计每个结点的入度，然后进行拓扑。
# 判断是否能够拓扑完即可，过程中统计入度为0的结点的个数。

# 建有向图图方法：邻接矩阵或者邻接表。
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # graph = [[]] * numCourses # python 使用不初始化的二维列表会出现问题。
        # n 个 []，对任意一个添加结点，其他的会同步添加。猜测是同一个引用。
        # 不推荐使用 * 的写法，可能出现 bug。
        graph = [[] for _ in range(numCourses)] # python
        indegree = [0 for _ in range(numCourses)]
        for order in prerequisites: # 建图
            start, end = order[1], order[0]
            graph[start].append(end)
            indegree[end] += 1
        s = []
        remain = 0 # 有多个入度不为0的结点
        for i in range(numCourses):
            if indegree[i] == 0:
                s.append(i)
            else:
                remain += 1
        while s:
            node = s.pop()
            for i in graph[node]:
                indegree[i] -= 1
                if indegree[i] == 0:
                    s.append(i)
                    remain -= 1
        return remain == 0

# 建完图后使用 DFS 或者 BFS也可。
