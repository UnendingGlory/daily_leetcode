#include <bits/stdc++.h>
using namespace std;

class Solution {
    // 并查集两个节点的父节点相同，则说明是冗余边
    vector<int> father;
public:
    /* 路径压缩：在搜索的过程中均赋值给顶层父节点
     * 使得下次访问时更快
     */
    int find(int x)
    {
        int z = x;
        while(x != father[x]) x = father[x];
        // 现在存的是根节点，接下来进行路径压缩
        while(z != father[z])
        {
            int a = z;
            z = father[z]; // 路径压缩
            father[a] = x;
        }
        return x;
    }

    void Union(int s, int e)
    {
        int fa = find(s), fb = find(s);
        if(fa != fb)
        {
            father[fa] = fb;
        }
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    // edges的size就是节点个数
        int n = edges.size();
        father.resize(n);
        for(int i = 1; i <= n; ++i) father[i] = i;
        for(auto i : edges)
        {
            int s = i[0], e = i[1];
            // 如果该边的两个端点父亲相同，则说明这条边是冗余边
            if(father[s] == father[e]) return {s, e};
            Union(s, e);
        }
        return {};
    }
};