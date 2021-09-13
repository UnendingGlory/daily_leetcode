#include "header.h"

// 将每个点当作回旋镖的拐点，假设有m个点到该点的距离相等，
// 由于需要考虑排列顺序，则有A(2, m) = m*(m-2+1) = m * (m - 1)个回旋镖
// 所以对于每个点，只需要统计所有点到points的距离
// 怎样统计数量？将距离作为哈希表的key值，数量作为value值即可

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int ans = 0;
        for (auto &p: points) {
            unordered_map<int, int> dist_cnt;
            for (auto &q : points) {
                int dist = (q[0] - p[0]) * (q[0] - p[0]) + (q[1] - p[1]) * (q[1] - p[1]);
                ++dist_cnt[dist];
            }
            for(auto tmp: dist_cnt) {
                ans += tmp.second * (tmp.second - 1);
            }
        }
        return ans;
    }
};
