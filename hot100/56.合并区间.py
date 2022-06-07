# 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi]。
# 请你合并所有重叠的区间，并返回 一个不重叠的区间数组。
# 输入：[[1,3],[2,6],[8,10],[15,18]]
# 输出：[[1,6],[8,10],[15,18]]

# 左端点排序后，如果合并区间的右端点比下一个区间的左端点还小，停止合并，加入答案数组。
# 否则则合并，由于左端点排序过，因此只需要合并右端点

from typing import List

class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort(key=lambda x: x[0]) # 按照第一个排序
        
        ans = []
        for interval in intervals:
            # 如果列表为空，或者可以停止合并
            if not ans or ans[-1][1] < interval[0]:
                ans.append(interval)
            else: # 否则和上一个区间合并
                ans[-1][1] = max(ans[-1][1], interval[1])
        return ans