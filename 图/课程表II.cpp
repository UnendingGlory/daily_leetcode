#include <bits/stdc++.h>
using namespace std;

// 深度或者广度优先搜索，或者直接暴力
class Solution {
public:
    vector<int> findOrder(int n, vector<vector<int>>& p) {
        int indegree[n], vis[n];
        memset(indegree, 0, sizeof(indegree));
        memset(vis, 0, sizeof(vis));
        vector<int> ans;
        // 领接矩阵
        vector<vector<int>> v(n);
        for(int i = 0; i < p.size(); ++i)
        {
            ++indegree[p[i][0]];
            v[p[i][1]].push_back(p[i][0]); // 指出去的边
        }
        while(ans.size() < n)
        {
            int i = 0;
            while(i < n)
            {
                if(indegree[i] == 0 && !vis[i])
                {
                    vis[i] = true;
                    break;
                }
                ++i;
            }
            if(i == n) return {};
            ans.push_back(i);
            for(int j = 0; j < v[i].size(); ++j) 
            {
                --indegree[v[i][j]];
            }
        }
        return ans;
    }   
};