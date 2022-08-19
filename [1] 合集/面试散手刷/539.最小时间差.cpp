#include "header.h"
// 给定一个 24 小时制（小时:分钟 "HH:MM"）的时间列表，
// 找出列表中任意两个时间的最小时间差并以分钟数表示。

// 输入：timePoints = ["23:59","00:00"]
// 输出：1
// 输入：timePoints = ["00:00","23:59","00:00"]
// 输出：0

// 2 <= timePoints.length <= 2 * 104
// timePoints[i] 格式为 "HH:MM"

// Solution1: 排序。
// 排序后最小时间差必定是相邻的差之一或者是最晚和最早时间之差。
// 注意需要将时间转换成分钟。
class Solution {
public:
    int getMinute(string &s) {
        return ((s[0] - '0') * 10 + s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
    }

    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        int ans = INT_MAX, pre = getMinute(timePoints[0]), first = pre;
        for (int i = 1; i < timePoints.size(); ++i) {
            int cur = getMinute(timePoints[i]);
            ans = min(ans, cur - pre);
            pre = cur;
        }
        // 最晚和最早时间差，得反过来计算
        ans = min(ans, first + 1440  - pre);
        return ans;
    }
};

// Solution2: 排序 + 抽屉原理优化。
// 抽屉原理：由于 24小时最多只有 1440 个分钟数。
//         因此如果 timePoints长度超过 1440，那么必然会有两个相同的时间，可以直接返回 0。
class Solution {
public:
    int getMinute(string &s) {
        return ((s[0] - '0') * 10 + s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
    }

    int findMinDifference(vector<string>& timePoints) {
        if (timePoints.size() > 1440) {
            return 0;
        }
        sort(timePoints.begin(), timePoints.end());
        int ans = INT_MAX, pre = getMinute(timePoints[0]), first = pre;
        for (int i = 1; i < timePoints.size(); ++i) {
            int cur = getMinute(timePoints[i]);
            ans = min(ans, cur - pre);
            pre = cur;
        }
        // 最晚和最早时间差，得反过来计算
        ans = min(ans, first + 1440  - pre);
        return ans;
    }
};
