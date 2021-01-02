#include "header.h"

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (!intervals.size()) return 0;
        sort(intervals.begin(), intervals.end(),  [](vector<int>& a, vector<int>& b) {
            return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
        });
        int right = intervals[0][1], ans = 0;
        for (int i = 1; i < intervals.size(); ++i) {
            if (right > intervals[i][0]) {
                // 区间不包含的情况
                ++ans;
                // 区间包含的情况
                if (right >= intervals[i][1]) {
                    right = intervals[i][1];
                }
            } else {
                right = intervals[i][1];
            }
        }
        return ans;
    }
};