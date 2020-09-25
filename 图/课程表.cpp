#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int c[numCourses], cnt = 0;
        vector<vector<int>> g(numCourses);
        memset(c, 0, sizeof(c));
        for(auto i : prerequisites)
            ++c[i[0]], g[i[1]].push_back(i[0]);
        // 拓扑排序，用队列存储入度为0的点
        queue<int> q;
        for(int i = 0; i < numCourses; ++i)
            if(!c[i]) q.push(i);
        while(!q.empty())
        {
            int x = q.front();
            printf("%d", x);
            q.pop();
            ++cnt; // pop掉一个计数1
            for(int i = 0; i < g[x].size(); ++i)
                if(--c[g[x][i]] == 0)
                    q.push(g[x][i]);
        }
        return cnt == numCourses;
    }
};