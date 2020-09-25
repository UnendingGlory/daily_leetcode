#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<int> father;
public:

    int find(int x)
    {
        int a = x;
        while(x != father[x]) x = father[x];
        // 路径压缩
        while(a != father[a])
        {
            int z = a;
            a = father[a];
            father[z] = x;
        }
        return x;
    }

    void Union(int s, int e)
    {
        int fa = find(s), fb = find(e);
        if(fa != fb) father[fb] = fa;
    }

    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        father.resize(n + 1);
        for(int i = 1; i <= n; ++i) father[i] = i;
        for(auto i : edges)
        {
            int u = i[0], v = i[1];
            // 如果father[v] != v，则说明v有两个父节点，则必定是冗余边
            if(father[v] != v)
            {
                return {u, v};
            }
            // 否则将两者Union
            Union(u, v);
            // 
        }
    }   
};