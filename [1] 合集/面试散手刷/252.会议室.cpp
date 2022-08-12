#include "header.h"

class Solution {
public:
    // 如果有会议冲突，即不能参加。
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) {
            return true;
        }
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b) {
            return (a[0] != b[0]) ? (a[0] < b[0]) : a[1] < b[1];
        });
        for (int i = 0; i < intervals.size() - 1; ++i) {
            if (intervals[i][1] > intervals[i+1][0]) {
                return false;
            }
        }
        return true;
    }
};