#include "header.h"

// 经典最小生成树Kruskal算法
// 每次选一条最小的边加入集合中
// 注意要求的是曼哈顿距离
// n个点选n-1条边
// 边的两端不能在同一个集合中
// 所以需要用并查集判断

struct edge {
    int _len;
    int _p1, _p2; // index for end-points
    edge (int len, int p1, int p2) : _len(len), _p1(p1), _p2(p2) {}
};

class UnionFindSet {
    vector<int> father;
public:
    UnionFindSet(int n) {
        father.resize(n);
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }

    int find(int x) {
        int z = x;
        while (x != father[x]) x = father[x];
        // path compress
        while (z != father[z]) {
            int father_z = father[z];
            father[z] = x;
            z = father_z;
        }
        return x;
    }

    void union_ab(int a, int b) {
        int father_a  = find(a), father_b = find(b);
        if (father_a != father_b) {
            father[father_a] = father_b;
        }
    }
};

class Solution {
    vector<edge> edge_set;
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        auto dis = [&](int x, int y) -> int {
            // Manhattan distance
            return abs(points[x][0] - points[y][0]) + abs(points[x][1] - points[y][1]);
        };
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                edge_set.emplace_back(edge(dis(i, j), i, j));
            }
        }
        sort(edge_set.begin(), edge_set.end(), [](const edge& e1, const edge& e2){
            return e1._len < e2._len;
        });
        int ans = 0, cnt = 0; // cnt: n - 1 edges
        UnionFindSet ufs(n);
        for (const auto& e: edge_set) {
            if (ufs.find(e._p1) != ufs.find(e._p2)) {
                ufs.union_ab(e._p1, e._p2);
                ans += e._len;
                if (++cnt == n - 1) break;
            }
        }
        return ans;
    }
};