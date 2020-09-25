#include <bits/stdc++.h>
using namespace std;

// 先将区间按照左端点从大到小排序，能合并的区间必定是相邻的
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() == 0) return intervals;
        vector<vector<int>> ans;
        sort(intervals.begin(), intervals.end(), [&](const vector<int> a, const vector<int> b){
            return a[0] < b[0];});
        int left = intervals[0][0], right = intervals[0][1];
        for(int i = 0; i < intervals.size(); ++i)
        {
            if(intervals[i][0] <= right) // 合并,left不变
                right = max(right, intervals[i][1]);
            // 先将结果打入ans，后面的再单独成一个区间
            if(intervals[i][0] > right) 
            {
                ans.push_back({left, right});
                left = intervals[i][0], right = intervals[i][1];
            }
            if(i == intervals.size() - 1)
                ans.push_back({left, right});
        }
        return ans;
    }
};