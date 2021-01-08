#include "header.h"

// 并查集模板
class UnionSet {
private:
    vector<int> father;
    int _n;
public:
    UnionSet(int n) {
        _n = n;
        father.resize(n);
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }

    int find(int x) {
        int z = x;
        while (x != father[x]) x = father[x];
        // 找到根节点x后路径压缩
        while (z != father[z]) {
            int record = father[z];
            father[z] = x;
            z = record;
        }
        return x;
    }

    void union_ab(int a, int b) {
        int fatherA = find(a), fatherB = find(b);
        if (fatherA != fatherB) {
            father[fatherA] = fatherB;
        }
    }

    // 簇的数量
    int num_of_clusters() {
        int ret = 0;
        for (int i = 0; i < _n; ++i) {
            if(father[i] == i) {
                ++ret;
            }
        }
        return ret;
    }
};