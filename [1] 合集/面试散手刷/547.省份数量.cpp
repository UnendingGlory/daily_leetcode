#include "header.h"

// 有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。
// 省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。
// 给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。
// 返回矩阵中 省份 的数量。

// Solution：经典并查集
// Solution：经典并查集
class UnionFindSet {
public:
    vector<int> father;
    int counts = 0; // 非连通图数量
    UnionFindSet(int n) {
        father.resize(n);
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
        counts = n;
    }
    
    int find(int x) {
        int z = x;
        while (x != father[x]) {
            x = father[x];
        }
        // 路径压缩
        while (z != father[z]) {
            int tmp = father[z];
            father[z] = x;
            z = tmp;
        }
        return x;
    }

    void union_ab(int a, int b) {
        int father_a = find(a), father_b = find(b);
        if (father_a != father_b) {
            father[father_a] = father_b;
            --counts;
        }
    }

    int getCounts() {
        return this->counts;
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionFindSet ufs(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j] == 1) {
                    ufs.union_ab(i, j);
                }
            }
        }
        return ufs.getCounts();
    }
};