/***************************************************************************
 *  @file       UnionFindSet.h
 *  @author     Wilosn.Wang
 *  @date       12  Jan 2021
 *  @remark     可以以相对路径将该头文件包含进目标文件使用
				也可以#include <UnionFindSet.h>，然后以gcc -I加入路径的方式组合编译
 *  @note
 ***************************************************************************/

#ifndef UNIONFINDSET_H
#define UNIONFINDSET_H
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
#endif