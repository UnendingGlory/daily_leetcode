#include "header.h"

// 你的面前有一堵矩形的、由 n 行砖块组成的砖墙。这些砖块高度相同（也就是一个单位高）但是宽度不同。每一行砖块的宽度之和相等。
// 你现在要画一条 [自顶向下] 的、穿过 [最少] 砖块的垂线。如果你画的线只是从砖块的边缘经过，就不算穿过这块砖。
// 且不能沿着整个墙的边缘画线。
// 返回最少穿过的砖块数量。

// Solution：哈希表。
// 问题转化：求穿过最少的砖块数量即求穿过最多的间隙数量。
// 统计每一行的间隙位置，再统计所有行中哪些间隙出现的最多。
// 实例：[1, 2, 2, 1] : -==^^# 间隙位置: [1, 3, 5]
//      [3, 1, 2]    : ---=^^        : [3, 4]
//      [1, 3, 2]    : -===^^        : [1, 4]
//      [2, 4]       : --====        : [2]
//      [3, 1, 2]    : ---=^^        : [3, 4]
//      [1, 3, 1, 1] : -===^#        : [1, 4, 5]
// 间隙使用前缀统计即可，出现次数使用哈希表进行计数即可。
// 可以发现，位置 4在间隙位置中出现的最多。
// 因此答案：高度 - 间隙数 = 6 - 4 = 2。
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> counts;
        int h = wall.size(), w;
        int pre;
        for (int i = 0; i < h; ++i) {
            pre = 0;
            w = wall[i].size();
            for (int j = 0; j < w - 1; ++j) { // 除去边缘
                pre += wall[i][j];
                ++counts[pre];
            }
        }
        int interval = 0; // 间隙
        for (auto kv: counts) {
            interval = max(interval, kv.second);
        }
        return h - interval;
    }
};