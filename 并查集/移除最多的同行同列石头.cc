#include "header.h"

// 对于同行同列的石头看成一个连通图
// 则如果删除最多次即把这个图删除到只剩一个顶点
// （因为能够遍历，所以逆向就可以选同行同列删除到只有一个顶点)
// 所以最多能删除的石头 = 所有石头 - 连通分量个数

// 并查集中union的是每一个节点的行和列
// 但是行和列要区分开，比如一个[3,3]的点，行和列是不一样的
// 并查集底层是一维的没法区分，所以只能采用映射的方式
// 由题只行列值均<10000，所以将列值+10000即可

class Solution {
    unordered_map<int, int> father;
public:

    int find(int x) {
        // 初始化
        if (!father.count(x)) father[x] = x;
        int z = x;
        while (x != father[x]) x = father[x];
        // 路径压缩
        while (z != father[z]) {
            int father_z = father[z];
            father[z] = x;
            z = father_z;
        }
        return x;
    }

    void union_ab(int a, int b) {
        int father_a = find(a), father_b = find(b);
        if (father_a != father_b) {
            father[father_a] = father_b;
        }
    }

    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        for (const auto& pair : stones) {
            union_ab(pair[0], pair[1] + 10000);
        }
        int connected = 0;
        for (const auto& [son, parent] : father) {
            if (son == parent) {
                ++connected;
            }
        }
        return n - connected;
    }
};