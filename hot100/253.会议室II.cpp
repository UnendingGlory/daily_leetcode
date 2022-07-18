#include "header.h"

// 给你一个会议时间安排的数组 intervals, 每个会议时间都会包括开始和
// 结束的时间 intervals[i] = [starti, endi]，返回 所需会议室的最小数量。

// 输入：intervals = [[0,30], [5,10], [15,20]]
// 输出：2
// 解释：[0, 30]需要一个单独的会议室，[5, 10] 和 [15, 20] 可以共用一个会议室。
// 如果会议冲突，不想让开会的人等待，单独开一个会议室。

// 换种角度思考，如果目前已经分配了 n个会议室，那么如果有一组会议时间为 [a, b]。
// 那么从会人员会在这 n个会议室中查找是否有会议室空闲，
// 如果有会议室空闲，那么使用该会议室，可以使得会议室数量最少。

// Solution1: 直觉贪心，将区间按照开始时间进行排序，毕竟越早的会议越应该早安排。
// 对于新来的一个会议 intevals[i]，假设当前有 n个会议正在进行。
// 去查看这 n个会议的结束时间，记其中最早的为 earliest。
// 如果 intervals[i] 的开始时间 start < earliest，那么新开一个会议室。
// 如果 intervals[i] 的开始时间 start >= earliest，那么将 earliest会议对应的会议室腾出使用。

// 如何查找 n个正在进行的会议的最早结束时间？最简单的使用暴力，其次可以使用优先级队列（堆）优化时间复杂度。
// 处理完所有的会议后，堆的大小即开的房间数量，即答案。
// 或者维护一个中间变量记录也可。

// 如果自己手写，涉及到堆的插入、删除、堆排序过程。
// 时间复杂度：O(nlogn)，空间复杂度：O(n)
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) {
            return 0;
        }
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b) {
            return (a[0] != b[0]) ? (a[0] < b[0]) : a[1] < b[1];
        });
        priority_queue<int, vector<int>, greater<int>> pq; // 优先取小的
        int ans = 1;
        pq.push(intervals[0][1]); // 初始化一个会议室。
        for (int i = 1; i < intervals.size(); ++i) {
            int earliest = pq.top();
            if (earliest <= intervals[i][0]) {
                pq.pop();
            } else {
                ++ans;
            }
            pq.push(intervals[i][1]);
        }
        // return pq.size(); // 这种写法也可。
        return ans;
    }
};


// Solution2: 有序化。
// 由于我们并不关心到底是哪个会议结束。我们所需要的只是一些会议结束, 从而提供一个空房间。
// 因此可以将会议的开始时间和结束时间分开从小到大排序，使用双指针 s和 e考虑。
// 为什么可以这样做？因为当遍历到 s时，如果 start[s] > end[e]。
// 又有 end[e] 对应的会议的 开始时间 starting < end[e]。
// 即有 start[s] > end[e] > starting。
// 说明当遇到“会议结束”事件时，意味着某个较早开始的会议已经结束。
// 可以将该会议占用的空房间腾出给当前会议使用。

// 只需要两个指针 s和 e往后遍历。
// 如果 start[s] < end[e]，那么 ans++(安排一个房间), s++。
// 如果 start[s] >=  end[e]，那么 e++。
// s遍历到开始数组的尾端时结束即可。

// 时间复杂度：排序O(nlogn)，空间复杂度：O(n)。
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) {
            return 0;
        }
        vector<int> start, end;
        for (auto &i: intervals) {
            start.emplace_back(i[0]);
            end.emplace_back(i[1]);
        }
        std::sort(start.begin(), start.end());
        std::sort(end.begin(), end.end());
        int s = 0, e = 0, ans = 0;
        while (s < start.size()) {
            if (start[s] < end[e]) { // 安排一个房间
                ++ans;
            } else { // 将某房间空出
                ++e;
            }
            ++s;
        }
        return ans;
    }
};
