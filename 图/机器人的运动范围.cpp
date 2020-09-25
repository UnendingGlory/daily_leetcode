#include <bits/stdc++.h>
using namespace std;

class Solution {
    int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
public:

    int cntSum(int x)
    {
        int res = 0;
        while(x)
        {
            res += x % 10;
            x /= 10;
        }
        return res;
    }

    // 统计机器人能到达多少格子，应该从源点开始BFS
    int movingCount(int m, int n, int k) {
        int ans = 0; // k >= 0
        bool vis[m][n];
        memset(vis, 0, sizeof(vis));
        queue<pair<int, int>> Q;
        Q.push({0, 0});
        vis[0][0] = true;
        while(!Q.empty())
        {
            auto temp = Q.front();
            Q.pop();
            ++ans;
            int i = temp.first, j = temp.second;
            for(int id = 0; id < 4; ++id)
            {
                int newI = i + dx[id], newJ = j + dy[id];
                if(newI >= 0 && newI < m && newJ >= 0 && newJ < n && vis[newI][newJ] == false 
                    && cntSum(newI) + cntSum(newJ) <= k) // 数位之和
                {
                    Q.push({newI, newJ});
                    vis[newI][newJ] = true;
                }
            }
        }
        return ans;
    }
};